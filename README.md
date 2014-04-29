# HTTP server (REST & JSON) on [Spark core](https://www.spark.io/)

![alt text](https://s3.amazonaws.com/spark-website/spark.png "")

<a href="http://www.youtube.com/watch?feature=player_embedded&v=ifYkC7UdMVA
" target="_blank"><img src="http://img.youtube.com/vi/ifYkC7UdMVA/0.jpg" 
alt="Aller sur Youtube" width="560" border="10" /></a>

[Youtube](https://www.youtube.com/watch?v=ifYkC7UdMVA)


## EN : Local HTTP server (REST & JSON) for Sparkcore

This project implement a Http server on Sparkcore itself. Once compiled into the [Web IDE](https://www.spark.io/build), the server will be available at http://IP-SPARKCORE (port 80 by default)

### Common files of projects :
- slre.h
- slre.cpp
- HttpResponse.h
- HttpResponse.cpp
- HttpRequest.h
- HttpRequest.cpp
- http_parser.h
- http_parser.cpp

Thanks to :
- [SLRE: Super Light Regular Expression library](https://github.com/cesanta/slre)
- [Marcussacapuces91 Github / SparkCore-RESTserver ](https://github.com/Marcussacapuces91/SparkCore-RESTserver)
- [Joyent Github/ http-parser](https://github.com/joyent/http-parser)

### Projects
- Project 1 : spark-Web-Tinker.ino
- Project 2 : spark-Web-Compas.ino

## FR : Serveur HTTP REST et JSON pour Spark Core.

Ce projet permet de mettre en oeuvre un serveur sur le Spark core lui-même.
Un fois compilé dans le [Web IDE](https://www.spark.io/build), le serveur sera accessible à l'adresse http://IP-SPARKCORE (port :80 par défaut). Ce projet est un exemple permettant d'envisager d'autres projet.

Fichiers communs des projets (Rappel .h = fichier d'entête, .cpp = fichier de définition [Sources]) :
- slre.h : 
- slre.cpp :
- HttpResponse.h : 
- HttpResponse.cpp :
- HttpRequest.h :
- HttpRequest.cpp :
- http_parser.h :
- http_parser.cpp :

Remerciements à :
- [SLRE: Super Light Regular Expression library](https://github.com/cesanta/slre)
- [Marcussacapuces91 Github / SparkCore-RESTserver ](https://github.com/Marcussacapuces91/SparkCore-RESTserver)
- [Joyent Github/ http-parser](https://github.com/joyent/http-parser)

### Projets
- Projet 1 : spark-Web-Tinker.ino - Ce projet permet de contrôler D0-D7 [HIGH|LOW] soit par l'interface web, soit en requête HTTP de forme http://IP-Sparkcore/D0/on|off.
- Projet 2 : spark-Web-Compas.ino
