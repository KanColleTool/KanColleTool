// http://stackoverflow.com/questions/5786483
function string_as_unicode_escape(input) {
	function pad_four(input) {
		var l = input.length;
		if (l == 0) return '0000';
		if (l == 1) return '000' + input;
		if (l == 2) return '00' + input;
		if (l == 3) return '0' + input;
		return input;
	}
    
    var output = '';
    for (var i = 0, l = input.length; i < l; i++)
    	output += '\\u' + pad_four(input.charCodeAt(i).toString(16));
    return output;
}

function esc(o) {
	if(o === null)
		return null;
	else if(typeof o == 'string')
		return string_as_unicode_escape(o)
	else if(o instanceof Array)
	{
		var res = [];
		for(var i = 0; i < o.length; i++)
			res.push(esc(o[i]))
	}
	else if(typeof o == 'object')
	{
		var res = {};
		for(key in o)
			res[key] = esc(o[key])
		return res
	}
	else return o;
}

function(data) {
	for(var i = 0; i < data['api_data'].length; i++) {
		data['api_data'][i]['api_name'] = 'Jane Doe'
		data['api_data'][i]['api_yomi'] = 'Jane Doe'
	}
	return JSON.stringify(esc(data))
}
