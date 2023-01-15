from flask import abort, Flask, jsonify, send_file

app = Flask(__name__)

DUMMY_FILES = dict({
    "File1": {
        "summary": "Summary text of file 1"
    },
    "File2": {
        "summary": "Summary text of file 2"
    },
    "File3": {
        "summary": "Summary text of file 3"
    }
})

@app.route("/api/files")
def list_files():
    return jsonify(DUMMY_FILES)


@app.route("/api/download/file/<variant>")
def download_file(variant=None):
    if not variant in DUMMY_FILES:
        abort(404)
        
    return send_file(
        f"./dummy_files/{variant}.txt",
        as_attachment=True
    )


if __name__ == "__main__":
    # debug=True will cause flask to send detailed exception traceback in
    # the response body. this is useful when trying out requests from a browser
    app.run(host="0.0.0.0", port=3000, debug=True)
