FROM python:3.7-alpine
WORKDIR /code
ENV FLASK_APP=app.py
ENV FLASK_RUN_HOST=0.0.0.0
RUN apk update && apk add --no-cache postgresql-dev gcc musl-dev linux-headers
# install dependencies
RUN pip install --upgrade pip
COPY requirements.txt requirements.txt
RUN pip install -r requirements.txt
# copy project
EXPOSE 5000
COPY . .
CMD ["flask","run"]