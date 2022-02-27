import psycopg2
from psycopg2 import Error
import time
from sqlalchemy import PrimaryKeyConstraint
from flask import Flask
import sqlalchemy as sqla
from flask_sqlalchemy import SQLAlchemy

##Creando APP
app=Flask(__name__)

#Configurando config
#SQLALCHEMY_DATABASE_URI -> key value
#Each database has a different config string
#En el caso de postgres es: postgresql://postgres:password@localhost/flaskmovie
app.config.from_object("config.Config")

##Creado db objects y pasar la app
db=SQLAlchemy(app)

##Crear tablas y esquema de la base de datos
class Count(db.Model):
    id=db.Column(db.Integer, primary_key=True,autoincrement=True)
    countname=db.Column(db.String(80))

    def __init__(self,countname):
        self.countname=countname
    
    def __repr__(self):
        return '{}'.format(self.id)



#Funcion que me devuelve un contador
def get_hit_count():
    retries = 5
    try:
        me = Count('juan_mavelyn')
        db.session.add(me)
        db.session.commit()
        list=Count.query.all()
        ##Accedo al valor del último que inserté, que vendría siendo len(list)-1
        value=list[len(list)-1]
        #Si quisiera borrar el registro insertado
        #db.session.delete(me)
        #db.session.commit()
        return value
    except (Exception, Error) as error:
        if retries == 0:
            print("Error while connecting to PostgreSQL", error)
            raise error
        retries -= 1
        time.sleep(0.5)


@app.route('/')

def index():
    #Creo la tabla a partir del esquema
    db.create_all()
    db.session.commit()
    hits=get_hit_count()
    return 'hello {} times flask\n'.format(hits)

#Elimino tabla, para reiniciar secuencia
#db.drop_all()
#db.session.commit()
