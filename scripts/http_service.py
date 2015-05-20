from xplane import api
from flask import Flask, jsonify

app = Flask(__name__)

@app.route('/api/v1.0/xplmcounplugins')
def index():
    return jsonify(result=api.XPLMCountPlugins())  # @UndefinedVariable

app.run()
