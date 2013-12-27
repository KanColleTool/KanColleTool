#!/usr/bin/env python2
# coding=utf-8
import sys
import json
import urllib2

def make_tldata(data, key, exported_keys):
	outdata = {
		"key": key,
		"data": {}
	}
	
	for item in data:
		exported_item = {}
		for e_key in exported_keys:
			exported_item[e_key] = item[e_key]
		
		outdata['data'][item[key]] = exported_item
	
	return json.dumps(outdata, indent=4, sort_keys=True, ensure_ascii=False, encoding="utf-8")

def export(origfilename, tlfilename, key, exported_keys):
	with open(origfilename) as f:
		data = json.load(f)['api_data']
	
	tldata = make_tldata(data, key, exported_keys)
	
	with open(tlfilename, 'w') as f:
		f.write(tldata.encode('utf-8'))

if __name__ == '__main__':
	print "Processing Ship Data..."
	export("ship.json", "ship-tlbase.json", "api_id", ["api_yomi", "api_getmes", "api_sinfo"])
	print "Processing Slot Item Data..."
	export("slotitem.json", "slotitem-tlbase.json", "api_id", ["api_name", "api_info"])
