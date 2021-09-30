#!/usr/bin/python
# -*-coding:utf-8 -*-
import json
import os

import eventlet
eventlet.monkey_patch()
from flask_mqtt import Mqtt
from flask_socketio import SocketIO
from flask_cors import CORS
os.environ["LANG"] = "en_US.UTF-8"
from flask import Flask, request,render_template

app = Flask(__name__)
app.config['MQTT_CLIENT_ID'] = 'wechatesp'
app.config['MQTT_BROKER_URL'] = 't.xxx.fun'
app.config['MQTT_BROKER_PORT'] = 1883
app.config['MQTT_KEEPALIVE'] = 60
app.config['MQTT_USERNAME'] = 'xxx'
app.config['MQTT_PASSWORD'] = 'xxx'
CORS(app)
mqtt = Mqtt(app)
socketio = SocketIO(app)

@mqtt.on_disconnect()
def on_disconnect(client, userdata, rc):
    print("disconnecting reason  "  +str(rc))

@mqtt.on_connect()
def handle_connect(client, userdata, flags, rc):
    print('on connect')
    mqtt.subscribe('/xxx/p/wechatexpample/#')


@mqtt.on_message()
def handle_mqtt_message(client, userdata, message):
    print(message.payload)


@app.route('/', methods=['GET'])
def index():
    data = request.args.get('data')
    data = json.loads(data)
    mqtt.publish("/xxx/s/wechatexpample/%s"%data['deviceid'],data['action'])
    return json.dumps({"status":0})

if __name__ == '__main__':
    socketio.run(app, host='0.0.0.0', port=2345, use_reloader=False, debug=True)
