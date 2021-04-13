## Greenroom(system for entertainment in free time)

## Table of contents
* [General info](#general-info)
* [Technologies](#technologies)
* [Setup](#setup)
* [Running](#running)

## General info
This is main part of my system which can share i.e. music or mems. It'll also remind you about shopping and will communicate in other ways. It helps maintain balance i.e.in COVID-19. It should be
use with "HealthMonitor" and "Reminder". These are another project which I created. 
	
## Technologies
Project is created with:
* python version: 3.7
* Java version: 11.0.7
* mysql-connector-java library version: 5.1.35
	
## Setup
To setup this project on Windows you must first install a Docker for Windows.

This can be do it by visit this website: https://hub.docker.com/editions/community/docker-ce-desktop-windows/

...,then install it locally using Docker(using following commands):

```
$ bash
$ docker pull piotrit2015/greenroomos:1
$ docker container run -i -t --name greenroomOS piotrit2015/greenroomos
$ cd home
$ mkdir <username>
$ cd <username>
$ git clone https://github.com/PiotrIT2015/Greenroom.git
$ cd ./Greenroom
$ systemctl start docker
$ systemctl enable docker
$ docker-compose up
$ docker container run -d -p 8080:80 nextcloud
$ docker container run -d -p mariadb
```

How to configure Nextcloud with Apache on Ubuntu: https://www.youtube.com/watch?v=-tW3_cmGkns

## Running
To run this project:
* run several services(they send data to mobile apps i.e.shopping list, images or youtube's links)

```
$ cd ../io.greenroom/services/<certain-cervice>
$ gradle build
$ gradle run
```

* run Cellular Automata(GUI's module) in IntelliJ IDEA
* run FIRA(GUI's module) on SimurSot(This is a football game in which gamers can change how robots run).

SimurSot source code:https://github.com/fira-simurosot/FIRASim

To use rest of project's functionalities use following commands:

* To vote for resolution with other user:

```
$ cd ../io.greenroom/dao/gekon/src/engine/pp
$ javac Server.java
$ javac ServerInt.java
$ javac Client.java
$ javac MySQLTest.java
$ java Server
$ java Client
```

* To download future releases use following commands:

```
$ cd ../io.greenroom/dao/updater
$ python3.7 gh-download.py
```

* To scann your network use following commands:

```
$ cd ../io.greenroom/mapper/networktools
$ python3.7 netscan1.py
$ python3.7 netscan2.py
```


