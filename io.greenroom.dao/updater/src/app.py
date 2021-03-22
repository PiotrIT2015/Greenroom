import os
from flask import Flask, render_template, request
import zipfile

app = Flask(__name__)

APP_ROOT = os.path.dirname(os.path.abspath(__file__))

@app.route("/")
def index():
    return render_template("upload.html")

@app.route("/upload", methods=['POST'])
def upload():
    target = os.path.join(APP_ROOT, 'Greenroom/')
    print(target)

    if not os.path.isdir(target):
        os.mkdir(target)

    for file in request.files.getlist("file"):
        print(file)
        filename = file.filename
        destination = "/".join([target,filename])
        print(destination)
        zip_ref = zipfile.ZipFile(file, 'r')
        zip_ref.extractall(destination)
        #file.save(destination)

    return render_template("complete.html")

if __name__=="__main__":
    app.run(port=4555, debug=True)
    print("Server running")
    print("Press Ctrl-C to end")
