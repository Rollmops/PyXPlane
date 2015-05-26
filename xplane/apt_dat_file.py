import re
import itertools
from matplotlib.path import Path

class AptDatFile:
    
    
    DATA_FIELDS = {1: ('elevation', 'atc_tower', '_', 'icao', 'aiport_name'),
                   100: ('runway_width', 'runway_surface_type', 'runway_shoulder_surface_type', 'runway_smoothness', 'centre_line_lights', 'runway_edge_lighting', 'runway_auto_generate_distance_remaining_signs',
                                    ('runways', ('number',
                                                 'latitude_end',
                                                 'longitude_end',
                                                 'displaced_threshold_length',
                                                 'blast_pad_length',
                                                 'markings',
                                                 'approach_lighting',
                                                 'touchdown_zone',
                                                 'reil') 
                                     ) 
                                    ),
                            '101': ('water_runway_width', 'perimeter_buoys',
                                   ('water_runways', ('number',
                                                      'latitude_end',
                                                      'longitude_end')
                                    )
                                   ),
                            '102': ('helipad_designator')
                            }

    def __init__(self, filename, load=True):
        
        self.structure_definition = {1: self._parse_data_fields,
                                     100: self._parse_data_fields,
                                     120: self._parse_taxiway}
        
        self.filename = filename
        self.line_pattern = re.compile(r'^(\d+)\s+(.*)')
        self.data = dict()
        self.data['taxiways'] = []
        
        if load:
            self.load(self.filename)
            

    def load(self, filename):
        
        self.filename = filename
        with open(filename, 'r') as apt_dat_fp:
            line = apt_dat_fp.readline()
            while line:
                line_match = self.line_pattern.match(line)
                if line_match:
                    row = int(line_match.group(1))
                    data = line_match.group(2)
                    if row in self.structure_definition.keys():
                        self.structure_definition[row](row, data, apt_dat_fp)
                line = apt_dat_fp.readline()
                        

    def _parse_list(self, data_tuple, structure):
        key = structure[0]
        self.data[key] = [{}]
        pos = -1
        for counter, data_name in enumerate(zip(data_tuple, itertools.cycle(structure[1]))):
            if not counter % len(structure[1]):
                pos+=1
                self.data[key].append({})
            self.data[key][pos][data_name[1]] = data_name[0]


    def _parse_data_fields(self, row, data, fp):
        field_names = AptDatFile.DATA_FIELDS[row]
        data_fields = data.split()
        pos = 0
        for data, name in zip(data_fields, field_names):
            if isinstance(name, tuple):
                self._parse_list(data_fields[pos:], name)
                break
            else:
                self.data[name] = data
            pos+=1
        

    def _parse_taxiway(self, row, data, fp):

        def points_to_tuple(points):
            return tuple([float(i) for i in points.split()])
        
        row, points = self.line_pattern.match(fp.readline()).groups()
        codes = [Path.MOVETO]
        start_point = points_to_tuple(points)[:2]
        verts = [start_point]
        
        while row in ['111', '112', '113', '115']:
            row, points = self.line_pattern.match(fp.readline()).groups()
            if row in ['111', '113', '115']:
                codes.append(Path.LINETO)
                verts.append(points_to_tuple(points)[:2])
            elif row == '112':
                _points = points_to_tuple(points)
                codes.append(Path.CURVE3)
                verts.append(_points[:2])
                codes.append(Path.CURVE3)
                verts.append(_points[2:4])
            
        codes.append(Path.CLOSEPOLY)
        verts.append(start_point)
        self.data['taxiways'].append((data, Path(verts, codes)))