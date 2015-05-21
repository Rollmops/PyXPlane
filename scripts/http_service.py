from xplane import api  # @UnresolvedImport
from flask import Flask, jsonify

app = Flask(__name__)

@app.route('/')
def index():
    return 'PyXPlane HTTP Service is alive!'

@app.route('/api/v1.0/XPLMGetMyID')
def XPLMGetMyID():
    return jsonify(result=api.XPLMGetMyID())  # @UndefinedVariable

   
@app.route('/api/v1.0/XPLMCountPlugins')
def XPLMCountPlugins():
    return jsonify(result=api.XPLMCountPlugins())  # @UndefinedVariable


@app.route('/api/v1.0/XPLMGetNthPlugin/<int:index>')
def XPLMGetNthPlugin(index):
    return jsonify(result=api.XPLMGetNthPlugin(index))  # @UndefinedVariable


@app.route('/api/v1.0/XPLMFindPluginByPath/<path:path>')
def XPLMFindPluginByPath(path):
    return jsonify(result=api.XPLMFindPluginByPath(path))  # @UndefinedVariable


@app.route('/api/v1.0/XPLMFindPluginBySignature/<string:signature>')
def XPLMFindPluginBySignature(signature):
    return jsonify(result=api.XPLMFindPluginBySignature(signature))  # @UndefinedVariable


@app.route('/api/v1.0/XPLMGetPluginInfo/<int:pluginID>')
def XPLMGetPluginInfo(pluginID):
    info = api.XPLMGetPluginInfo(pluginID)  # @UndefinedVariable

    return jsonify(result={'outName': info[0],
                           'outFilePath': info[1],
                           'outSignature': info[2],
                           'outDescription': info[3]
                           }) 


app.run()
