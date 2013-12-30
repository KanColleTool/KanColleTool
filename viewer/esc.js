function esc(o) {
	if(o === null)
		return null;
	else if(typeof o == 'string')
		return escape(o).replace(/\%/g, '\\')
	else if(o instanceof Array)
	{
		var res = [];
		for(var i = 0; i < o.length; i++)
			res.push_back(esc(o[i]))
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
