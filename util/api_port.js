// u = The current user's ID
function _(u) {
	var loc = [1171, 1841, 2517, 3101, 4819, 5233, 6311, 7977, 8103, 9377, 1000]
	var ret = 
		(loc[10] + u % loc[10]).toString() +
		(
			(9.999999999E9 -
				Math.floor(new Date().getTime() / loc[10]) -
				u
			) * loc[u % 10]
		).toString() +
		cN() + cN() + cN() + cN();
	return ret;
}

function cN() {
	return Math.floor(Math.random() * 10).toString();
}
