# Mosquitto


## Installation

```shell
sudo apt-get install mosquitto
```


update mosquitto config:

```
sudo touch /etc/mosquitto/conf.d/websocket.conf
sudo leafpad /etc/mosquitto/conf.d/websocket.conf
```

```
listener 1883
protocol mqtt

listener 9001
protocol websockets
```

restart mosquitto

```
sudo systemctl restart mosquitto
```