# Script for testing Chunked Responses by replaying an old /kcsapi/api_start2
# Requires Flask to work

import os
from flask import Flask, Response, stream_with_context, g
import time

app = Flask(__name__)

# I think 893 + <header size> for that request added up to 1KB or something
chunk_size = 893

@app.route('/', methods=['GET', 'POST'])
def index():
	global resp
	def read_chunks():
		with open(os.path.join(os.path.dirname(__file__), 'chunkserver_data.txt')) as f:
			while True:
				chunk = f.read(chunk_size)
				if not chunk:
					break
				yield chunk
				#time.sleep(1)
	return Response(stream_with_context(read_chunks()), mimetype='text/plain')

if __name__ == '__main__':
	app.run(debug=True)

