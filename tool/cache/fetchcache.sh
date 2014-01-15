#!/bin/bash

if [ $# -ne 3 ]; then
	echo "Usage: fetchcache.sh [server_ip] [api_token] [endpoint]"
	echo ""
	echo "  [server_ip] = The IP of your server (ex. 125.6.189.71)."
	echo "                You must use the server in your API Link, or you'll get errors."
	echo "  [api_token] = Your API Token (a string of 40 hex characters)."
	echo "  [endpoint] = The endpoint you want to capture (ex. api_get_master/ship)"
	echo "               (note that this must /not/ include a leading or trailing slash)"
	echo ""
	echo "Ex.: ./fetchcache.sh 125.6.189.71 9c3cf114... api_get_master/ship"
	echo "------------------------------------------------------------------------------"
	echo ""
	echo "If you don't know what your Server IP or API Token are, look at your API Link:"
	echo "(If you don't know what that is, read http://waa.ai/puO)"
	echo ""
	echo "  http://[server_ip]/kcs/mainD2.swf?api_token=[api_token]&api_starttime=..."
	echo ""
	echo "Ignore the \"&api_starttime=...\" part; it's unimportant and uninteresting."
	echo "The only parts that are interesting are the Server IP and API Token."
	exit
fi

CACHEDIR=$(dirname "${BASH_SOURCE[0]}")

SERVER_IP=$1
API_TOKEN=$2
ENDPOINT=$3

OUTPATH=$CACHEDIR/$ENDPOINT.json
mkdir -p `dirname $OUTPATH`

# Note: tail -c+8 cuts off the 'svdata=' prefix on JSON responses
curl --referer "http://${SERVER_IP}/kcs/mainD2.swf?api_token=${API_TOKEN}" --data "api_token=${API_TOKEN}&api_verno=1" "http://${SERVER_IP}/kcsapi/${ENDPOINT}" | tail -c+8 | python -mjson.tool > $OUTPATH
