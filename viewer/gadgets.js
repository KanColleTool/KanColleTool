var gadgets = gadgets || {};
var shindig = shindig || {};
var osapi = osapi || {};
gadgets.config = function () {
    var components = {};
    var configuration;
    return {
        'register': function (component, opt_validators, opt_callback) {
            var registered = components[component];
            if (!registered) {
                registered = [];
                components[component] = registered;
            }
            registered.push({
                validators: opt_validators || {},
                callback: opt_callback
            });
        },
        'get': function (opt_component) {
            if (opt_component) {
                return configuration[opt_component] || {};
            }
            return configuration;
        },
        'init': function (config, opt_noValidation) {
            configuration = config;
            for (var name in components) {
                if (components.hasOwnProperty(name)) {
                    var componentList = components[name],
                        conf = config[name];
                    for (var i = 0, j = componentList.length; i < j; ++i) {
                        var component = componentList[i];
                        if (conf && !opt_noValidation) {
                            var validators = component.validators;
                            for (var v in validators) {
                                if (validators.hasOwnProperty(v)) {
                                    if (!validators[v](conf[v])) {
                                        throw new Error('Invalid config value "' + conf[v] + '" for parameter "' + v + '" in component "' +
                                            name + '"');
                                    }
                                }
                            }
                        }
                        if (component.callback) {
                            component.callback(config);
                        }
                    }
                }
            }
        },
        'EnumValidator': function (list) {
            var listItems = [];
            if (arguments.length > 1) {
                for (var i = 0, arg;
                    (arg = arguments[i]); ++i) {
                    listItems.push(arg);
                }
            } else {
                listItems = list;
            }
            return function (data) {
                for (var i = 0, test;
                    (test = listItems[i]); ++i) {
                    if (data === listItems[i]) {
                        return true;
                    }
                }
                return false;
            };
        },
        'RegExValidator': function (re) {
            return function (data) {
                return re.test(data);
            };
        },
        'ExistsValidator': function (data) {
            return typeof data !== "undefined";
        },
        'NonEmptyStringValidator': function (data) {
            return typeof data === "string" && data.length > 0;
        },
        'BooleanValidator': function (data) {
            return typeof data === "boolean";
        },
        'LikeValidator': function (test) {
            return function (data) {
                for (var member in test) {
                    if (test.hasOwnProperty(member)) {
                        var t = test[member];
                        if (!t(data[member])) {
                            return false;
                        }
                    }
                }
                return true;
            };
        }
    };
}();
gadgets.config.isGadget = true;
gadgets.config.isContainer = false;
if (window.JSON && window.JSON.parse && window.JSON.stringify) {
    gadgets['json'] = (function () {
        var endsWith___ = /___$/;
        return {
            'parse': function (str) {
                try {
                    return window.JSON.parse(str);
                } catch (e) {
                    return false;
                }
            },
            'stringify': function (obj) {
                try {
                    return window.JSON.stringify(obj, function (k, v) {
                        return !endsWith___.test(k) ? v : null;
                    });
                } catch (e) {
                    return null;
                }
            }
        };
    })();
} else {
    gadgets['json'] = function () {
        function f(n) {
            return n < 10 ? '0' + n : n;
        }
        Date.prototype.toJSON = function () {
            return [this.getUTCFullYear(), '-', f(this.getUTCMonth() + 1), '-', f(this.getUTCDate()), 'T', f(this.getUTCHours()), ':', f(this.getUTCMinutes()), ':', f(this.getUTCSeconds()), 'Z'].join("");
        };
        var m = {
            '\b': '\\b',
            '\t': '\\t',
            '\n': '\\n',
            '\f': '\\f',
            '\r': '\\r',
            '"': '\\"',
            '\\': '\\\\'
        };

        function stringify(value) {
            var a, i, k, l, r = /["\\\x00-\x1f\x7f-\x9f]/g,
                v;
            switch (typeof value) {
            case 'string':
                return r.test(value) ? '"' + value.replace(r, function (a) {
                    var c = m[a];
                    if (c) {
                        return c;
                    }
                    c = a.charCodeAt();
                    return '\\u00' + Math.floor(c / 16).toString(16) +
                        (c % 16).toString(16);
                }) + '"' : '"' + value + '"';
            case 'number':
                return isFinite(value) ? String(value) : 'null';
            case 'boolean':
            case 'null':
                return String(value);
            case 'object':
                if (!value) {
                    return 'null';
                }
                a = [];
                if (typeof value.length === 'number' && !value.propertyIsEnumerable('length')) {
                    l = value.length;
                    for (i = 0; i < l; i += 1) {
                        a.push(stringify(value[i]) || 'null');
                    }
                    return '[' + a.join(',') + ']';
                }
                for (k in value) {
                    if (k.match('___$'))
                        continue;
                    if (value.hasOwnProperty(k)) {
                        if (typeof k === 'string') {
                            v = stringify(value[k]);
                            if (v) {
                                a.push(stringify(k) + ':' + v);
                            }
                        }
                    }
                }
                return '{' + a.join(',') + '}';
            }
            return "undefined";
        }
        return {
            'stringify': stringify,
            'parse': function (text) {
                if (/^[\],:{}\s]*$/.test(text.replace(/\\["\\\/b-u]/g, '@').replace(/"[^"\\\n\r]*"|true|false|null|-?\d+(?:\.\d*)?(?:[eE][+\-]?\d+)?/g, ']').replace(/(?:^|:|,)(?:\s*\[)+/g, ''))) {
                    return eval('(' + text + ')');
                }
                return false;
            }
        };
    }();
}
gadgets['json'].flatten = function (obj) {
    var flat = {};
    if (obj === null || obj === undefined) return flat;
    for (var k in obj) {
        if (obj.hasOwnProperty(k)) {
            var value = obj[k];
            if (null === value || undefined === value) {
                continue;
            }
            flat[k] = (typeof value === 'string') ? value : gadgets.json.stringify(value);
        }
    }
    return flat;
}
var tamings___ = tamings___ || [];
tamings___.push(function (imports) {
    ___.tamesTo(gadgets.json.stringify, safeJSON.stringify);
    ___.tamesTo(gadgets.json.parse, safeJSON.parse);
});
gadgets['util'] = function () {
    function parseUrlParams(url) {
        var query;
        var queryIdx = url.indexOf("?");
        var hashIdx = url.indexOf("#");
        if (hashIdx === -1) {
            query = url.substr(queryIdx + 1);
        } else {
            query = [url.substr(queryIdx + 1, hashIdx - queryIdx - 1), "&", url.substr(hashIdx + 1)].join("");
        }
        return query.split("&");
    }
    var parameters = null;
    var features = {};
    var services = {};
    var onLoadHandlers = [];
    var escapeCodePoints = {
        0: false,
        10: true,
        13: true,
        34: true,
        39: true,
        60: true,
        62: true,
        92: true,
        8232: true,
        8233: true
    };

    function unescapeEntity(match, value) {
        return String.fromCharCode(value);
    }

    function init(config) {
        features = config["core.util"] || {};
    }
    if (gadgets.config) {
        gadgets.config.register("core.util", null, init);
    }
    return {
        'getUrlParameters': function (opt_url) {
            var no_opt_url = typeof opt_url === "undefined";
            if (parameters !== null && no_opt_url) {
                return parameters;
            }
            var parsed = {};
            var pairs = parseUrlParams(opt_url || document.location.href);
            var unesc = window.decodeURIComponent ? decodeURIComponent : unescape;
            for (var i = 0, j = pairs.length; i < j; ++i) {
                var pos = pairs[i].indexOf('=');
                if (pos === -1) {
                    continue;
                }
                var argName = pairs[i].substring(0, pos);
                var value = pairs[i].substring(pos + 1);
                value = value.replace(/\+/g, " ");
                parsed[argName] = unesc(value);
            }
            if (no_opt_url) {
                parameters = parsed;
            }
            return parsed;
        },
        'makeClosure': function (scope, callback, var_args) {
            var baseArgs = [];
            for (var i = 2, j = arguments.length; i < j; ++i) {
                baseArgs.push(arguments[i]);
            }
            return function () {
                var tmpArgs = baseArgs.slice();
                for (var i = 0, j = arguments.length; i < j; ++i) {
                    tmpArgs.push(arguments[i]);
                }
                return callback.apply(scope, tmpArgs);
            };
        },
        'makeEnum': function (values) {
            var i, v, obj = {};
            for (i = 0;
                (v = values[i]); ++i) {
                obj[v] = v;
            }
            return obj;
        },
        'getFeatureParameters': function (feature) {
            return typeof features[feature] === "undefined" ? null : features[feature];
        },
        'hasFeature': function (feature) {
            return typeof features[feature] !== "undefined";
        },
        'getServices': function () {
            return services;
        },
        'registerOnLoadHandler': function (callback) {
            onLoadHandlers.push(callback);
        },
        'runOnLoadHandlers': function () {
            for (var i = 0, j = onLoadHandlers.length; i < j; ++i) {
                onLoadHandlers[i]();
            }
        },
        'escape': function (input, opt_escapeObjects) {
            if (!input) {
                return input;
            } else if (typeof input === "string") {
                return gadgets.util.escapeString(input);
            } else if (typeof input === "array") {
                for (var i = 0, j = input.length; i < j; ++i) {
                    input[i] = gadgets.util.escape(input[i]);
                }
            } else if (typeof input === "object" && opt_escapeObjects) {
                var newObject = {};
                for (var field in input) {
                    if (input.hasOwnProperty(field)) {
                        newObject[gadgets.util.escapeString(field)] = gadgets.util.escape(input[field], true);
                    }
                }
                return newObject;
            }
            return input;
        },
        'escapeString': function (str) {
            if (!str) return str;
            var out = [],
                ch, shouldEscape;
            for (var i = 0, j = str.length; i < j; ++i) {
                ch = str.charCodeAt(i);
                shouldEscape = escapeCodePoints[ch];
                if (shouldEscape === true) {
                    out.push("&#", ch, ";");
                } else if (shouldEscape !== false) {
                    out.push(str.charAt(i));
                }
            }
            return out.join("");
        },
        'unescapeString': function (str) {
            if (!str) return str;
            return str.replace(/&#([0-9]+);/g, unescapeEntity);
        },
        'attachBrowserEvent': function (elem, eventName, callback, useCapture) {
            if (typeof elem.addEventListener != 'undefined') {
                elem.addEventListener(eventName, callback, useCapture);
            } else if (typeof elem.attachEvent != 'undefined') {
                elem.attachEvent('on' + eventName, callback);
            } else {
                gadgets.warn("cannot attachBrowserEvent: " + eventName);
            }
        },
        'removeBrowserEvent': function (elem, eventName, callback, useCapture) {
            if (elem.removeEventListener) {
                elem.removeEventListener(eventName, callback, useCapture);
            } else if (elem.detachEvent) {
                elem.detachEvent('on' + eventName, callback);
            } else {
                gadgets.warn("cannot removeBrowserEvent: " + eventName);
            }
        }
    };
}();
gadgets['util'].getUrlParameters();
var tamings___ = tamings___ || [];
tamings___.push(function (imports) {
    caja___.whitelistFuncs([
        [gadgets.util, 'escapeString'],
        [gadgets.util, 'getFeatureParameters'],
        [gadgets.util, 'getUrlParameters'],
        [gadgets.util, 'hasFeature'],
        [gadgets.util, 'registerOnLoadHandler'],
        [gadgets.util, 'unescapeString']
    ]);
});
(function () {
    var instance = null;
    var prefs = {};
    var esc = gadgets.util.escapeString;
    var messages = {};
    var defaultPrefs = {};
    var language = "en";
    var country = "US";
    var moduleId = 0;

    function parseUrl() {
        var params = gadgets.util.getUrlParameters();
        for (var i in params) {
            if (params.hasOwnProperty(i)) {
                if (i.indexOf("up_") === 0 && i.length > 3) {
                    prefs[i.substr(3)] = String(params[i]);
                } else if (i === "country") {
                    country = params[i];
                } else if (i === "lang") {
                    language = params[i];
                } else if (i === "mid") {
                    moduleId = params[i];
                }
            }
        }
    }

    function mergeDefaults() {
        for (var name in defaultPrefs) {
            if (typeof prefs[name] === 'undefined') {
                prefs[name] = defaultPrefs[name];
            }
        }
    }
    gadgets.Prefs = function () {
        if (!instance) {
            parseUrl();
            mergeDefaults();
            instance = this;
        }
        return instance;
    };
    gadgets.Prefs.setInternal_ = function (key, value) {
        var wasModified = false;
        if (typeof key === "string") {
            if (!prefs.hasOwnProperty(key) || prefs[key] !== value) {
                wasModified = true;
            }
            prefs[key] = value;
        } else {
            for (var k in key) {
                if (key.hasOwnProperty(k)) {
                    var v = key[k];
                    if (!prefs.hasOwnProperty(k) || prefs[k] !== v) {
                        wasModified = true;
                    }
                    prefs[k] = v;
                }
            }
        }
        return wasModified;
    };
    gadgets.Prefs.setMessages_ = function (msgs) {
        messages = msgs;
    };
    gadgets.Prefs.setDefaultPrefs_ = function (defprefs) {
        defaultPrefs = defprefs;
    };
    gadgets.Prefs.prototype.getString = function (key) {
        if (key === ".lang") {
            key = "lang";
        }
        return prefs[key] ? esc(prefs[key]) : "";
    };
    gadgets.Prefs.prototype.setDontEscape_ = function () {
        esc = function (k) {
            return k;
        };
    };
    gadgets.Prefs.prototype.getInt = function (key) {
        var val = parseInt(prefs[key], 10);
        return isNaN(val) ? 0 : val;
    };
    gadgets.Prefs.prototype.getFloat = function (key) {
        var val = parseFloat(prefs[key]);
        return isNaN(val) ? 0 : val;
    };
    gadgets.Prefs.prototype.getBool = function (key) {
        var val = prefs[key];
        if (val) {
            return val === "true" || val === true || !! parseInt(val, 10);
        }
        return false;
    };
    gadgets.Prefs.prototype.set = function (key, value) {
        throw new Error("setprefs feature required to make this call.");
    };
    gadgets.Prefs.prototype.getArray = function (key) {
        var val = prefs[key];
        if (val) {
            var arr = val.split("|");
            for (var i = 0, j = arr.length; i < j; ++i) {
                arr[i] = esc(arr[i].replace(/%7C/g, "|"));
            }
            return arr;
        }
        return [];
    };
    gadgets.Prefs.prototype.setArray = function (key, val) {
        throw new Error("setprefs feature required to make this call.");
    };
    gadgets.Prefs.prototype.getMsg = function (key) {
        return messages[key] || "";
    };
    gadgets.Prefs.prototype.getCountry = function () {
        return country;
    };
    gadgets.Prefs.prototype.getLang = function () {
        return language;
    };
    gadgets.Prefs.prototype.getModuleId = function () {
        return moduleId;
    };
})();
var tamings___ = tamings___ || [];
tamings___.push(function (imports) {
    caja___.whitelistCtors([
        [gadgets, 'Prefs', Object]
    ]);
    caja___.whitelistMeths([
        [gadgets.Prefs, 'getArray'],
        [gadgets.Prefs, 'getBool'],
        [gadgets.Prefs, 'getCountry'],
        [gadgets.Prefs, 'getFloat'],
        [gadgets.Prefs, 'getInt'],
        [gadgets.Prefs, 'getLang'],
        [gadgets.Prefs, 'getMsg'],
        [gadgets.Prefs, 'getString'],
        [gadgets.Prefs, 'set'],
        [gadgets.Prefs, 'setArray']
    ]);
});
shindig.Auth = function () {
    var authToken = null;
    var trusted = null;

    function addParamsToToken(urlParams) {
        var args = authToken.split('&');
        for (var i = 0; i < args.length; i++) {
            var nameAndValue = args[i].split('=');
            if (nameAndValue.length === 2) {
                var name = nameAndValue[0];
                var value = nameAndValue[1];
                if (value === '$') {
                    value = encodeURIComponent(urlParams[name]);
                    args[i] = name + '=' + value;
                }
            }
        }
        authToken = args.join('&');
    }

    function init(configuration) {
        var urlParams = gadgets.util.getUrlParameters();
        var config = configuration["shindig.auth"] || {};
        if (config.authToken) {
            authToken = config.authToken;
        } else if (urlParams.st) {
            authToken = urlParams.st;
        }
        if (authToken !== null) {
            addParamsToToken(urlParams);
        }
        if (config.trustedJson) {
            trusted = eval("(" + config.trustedJson + ")");
        }
    }
    gadgets.config.register("shindig.auth", null, init);
    return {
        getSecurityToken: function () {
            return authToken;
        },
        updateSecurityToken: function (newToken) {
            authToken = newToken;
        },
        getTrustedData: function () {
            return trusted;
        }
    };
};
shindig.auth = new shindig.Auth();
gadgets.io = function () {
    var config = {};
    var oauthState;

    function makeXhr() {
        var x;
        if (typeof shindig != 'undefined' && shindig.xhrwrapper && shindig.xhrwrapper.createXHR) {
            return shindig.xhrwrapper.createXHR();
        } else if (typeof ActiveXObject != 'undefined') {
            x = new ActiveXObject("Msxml2.XMLHTTP");
            if (!x) {
                x = new ActiveXObject("Microsoft.XMLHTTP");
            }
            return x;
        } else if (typeof XMLHttpRequest != 'undefined' || window.XMLHttpRequest) {
            return new window.XMLHttpRequest();
        } else throw ("no xhr available");
    }

    function hadError(xobj, callback) {
        if (xobj.readyState !== 4) {
            return true;
        }
        try {
            if (xobj.status !== 200) {
                var error = ("" + xobj.status);
                if (xobj.responseText) {
                    error = error + " " + xobj.responseText;
                }
                callback({
                    errors: [error],
                    rc: xobj.status,
                    text: xobj.responseText
                });
                return true;
            }
        } catch (e) {
            callback({
                errors: [e.number + " Error not specified"],
                rc: e.number,
                text: e.description
            });
            return true;
        }
        return false;
    }

    function processNonProxiedResponse(url, callback, params, xobj) {
        if (hadError(xobj, callback)) {
            return;
        }
        var data = {
            body: xobj.responseText
        };
        callback(transformResponseData(params, data));
    }
    var UNPARSEABLE_CRUFT = "throw 1; < don't be evil' >";

    function processResponse(url, callback, params, xobj) {
        if (hadError(xobj, callback)) {
            return;
        }
        var txt = xobj.responseText;
        var offset = txt.indexOf(UNPARSEABLE_CRUFT) + UNPARSEABLE_CRUFT.length;
        if (offset < UNPARSEABLE_CRUFT.length) return;
        txt = txt.substr(offset)
        var data = eval("(" + txt + ")");
        data = data[url];
        if (data.oauthState) {
            oauthState = data.oauthState;
        }
        if (data.st) {
            shindig.auth.updateSecurityToken(data.st);
        }
        callback(transformResponseData(params, data));
    }

    function transformResponseData(params, data) {
        var resp = {
            text: data.body,
            rc: data.rc || 200,
            headers: data.headers,
            oauthApprovalUrl: data.oauthApprovalUrl,
            oauthError: data.oauthError,
            oauthErrorText: data.oauthErrorText,
            errors: []
        };
        if (resp.rc < 200 || resp.rc >= 400) {
            resp.errors = [resp.rc + " Error"];
        } else if (resp.text) {
            if (resp.rc >= 300 && resp.rc < 400) {
                params.CONTENT_TYPE = "TEXT";
            }
            switch (params.CONTENT_TYPE) {
            case "JSON":
            case "FEED":
                resp.data = gadgets.json.parse(resp.text);
                if (!resp.data) {
                    resp.errors.push("500 Failed to parse JSON");
                    resp.rc = 500;
                    resp.data = null;
                }
                break;
            case "DOM":
                var dom;
                if (typeof ActiveXObject != 'undefined') {
                    dom = new ActiveXObject("Microsoft.XMLDOM");
                    dom.async = false;
                    dom.validateOnParse = false;
                    dom.resolveExternals = false;
                    if (!dom.loadXML(resp.text)) {
                        resp.errors.push("500 Failed to parse XML");
                        resp.rc = 500;
                    } else {
                        resp.data = dom;
                    }
                } else {
                    var parser = new DOMParser();
                    dom = parser.parseFromString(resp.text, "text/xml");
                    if ("parsererror" === dom.documentElement.nodeName) {
                        resp.errors.push("500 Failed to parse XML");
                        resp.rc = 500;
                    } else {
                        resp.data = dom;
                    }
                }
                break;
            default:
                resp.data = resp.text;
                break;
            }
        }
        return resp;
    }

    function makeXhrRequest(realUrl, proxyUrl, callback, paramData, method, params, processResponseFunction, opt_contentType) {
        var xhr = makeXhr();
        if (proxyUrl.indexOf('//') == 0) {
            proxyUrl = document.location.protocol + proxyUrl;
        }
        xhr.open(method, proxyUrl, true);
        if (callback) {
            xhr.onreadystatechange = gadgets.util.makeClosure(null, processResponseFunction, realUrl, callback, params, xhr);
        }
        if (paramData !== null) {
            xhr.setRequestHeader('Content-Type', opt_contentType || 'application/x-www-form-urlencoded');
            xhr.send(paramData);
        } else {
            xhr.send(null);
        }
    }

    function respondWithPreload(postData, params, callback) {
        if (gadgets.io.preloaded_ && postData.httpMethod === "GET") {
            for (var i = 0; i < gadgets.io.preloaded_.length; i++) {
                var preload = gadgets.io.preloaded_[i];
                if (preload && (preload.id === postData.url)) {
                    delete gadgets.io.preloaded_[i];
                    if (preload.rc !== 200) {
                        callback({
                            rc: preload.rc,
                            errors: [preload.rc + " Error"]
                        });
                    } else {
                        if (preload.oauthState) {
                            oauthState = preload.oauthState;
                        }
                        var resp = {
                            body: preload.body,
                            rc: preload.rc,
                            headers: preload.headers,
                            oauthApprovalUrl: preload.oauthApprovalUrl,
                            oauthError: preload.oauthError,
                            oauthErrorText: preload.oauthErrorText,
                            errors: []
                        };
                        callback(transformResponseData(params, resp));
                    }
                    return true;
                }
            }
        }
        return false;
    }

    function init(configuration) {
        config = configuration["core.io"] || {};
    }
    var requiredConfig = {
        proxyUrl: new gadgets.config.RegExValidator(/.*%(raw)?url%.*/),
        jsonProxyUrl: gadgets.config.NonEmptyStringValidator
    };
    gadgets.config.register("core.io", requiredConfig, init);
    return {
        makeRequest: function (url, callback, opt_params) {
            var params = opt_params || {};
            var httpMethod = params.METHOD || "GET";
            var refreshInterval = params.REFRESH_INTERVAL;
            var auth, st;
            if (params.AUTHORIZATION && params.AUTHORIZATION !== "NONE") {
                auth = params.AUTHORIZATION.toLowerCase();
                st = shindig.auth.getSecurityToken();
            } else {
                if (httpMethod === "GET" && refreshInterval === undefined) {
                    refreshInterval = 3600;
                }
            }
            var signOwner = true;
            if (typeof params.OWNER_SIGNED !== "undefined") {
                signOwner = params.OWNER_SIGNED;
            }
            var signViewer = true;
            if (typeof params.VIEWER_SIGNED !== "undefined") {
                signViewer = params.VIEWER_SIGNED;
            }
            var headers = params.HEADERS || {};
            if (httpMethod === "POST" && !headers["Content-Type"]) {
                headers["Content-Type"] = "application/x-www-form-urlencoded";
            }
            var urlParams = gadgets.util.getUrlParameters();
            var paramData = {
                url: url,
                httpMethod: httpMethod,
                headers: gadgets.io.encodeValues(headers, false),
                postData: params.POST_DATA || "",
                authz: auth || "",
                st: st || "",
                contentType: params.CONTENT_TYPE || "TEXT",
                numEntries: params.NUM_ENTRIES || "3",
                getSummaries: !! params.GET_SUMMARIES,
                signOwner: signOwner,
                signViewer: signViewer,
                gadget: urlParams.url,
                container: urlParams.container || urlParams.synd || "default",
                bypassSpecCache: gadgets.util.getUrlParameters().nocache || "",
                getFullHeaders: !! params.GET_FULL_HEADERS
            };
            if (auth === "oauth" || auth === "signed") {
                if (gadgets.io.oauthReceivedCallbackUrl_) {
                    paramData.OAUTH_RECEIVED_CALLBACK = gadgets.io.oauthReceivedCallbackUrl_;
                    gadgets.io.oauthReceivedCallbackUrl_ = null;
                }
                paramData.oauthState = oauthState || "";
                for (var opt in params) {
                    if (params.hasOwnProperty(opt)) {
                        if (opt.indexOf("OAUTH_") === 0) {
                            paramData[opt] = params[opt];
                        }
                    }
                }
            }
            var proxyUrl = config.jsonProxyUrl.replace("%host%", document.location.host);
            if (!respondWithPreload(paramData, params, callback, processResponse)) {
                if (httpMethod === "GET" && refreshInterval > 0) {
                    var extraparams = "?refresh=" + refreshInterval + '&' + gadgets.io.encodeValues(paramData);
                    makeXhrRequest(url, proxyUrl + extraparams, callback, null, "GET", params, processResponse);
                } else {
                    makeXhrRequest(url, proxyUrl, callback, gadgets.io.encodeValues(paramData), "POST", params, processResponse);
                }
            }
        },
        makeNonProxiedRequest: function (relativeUrl, callback, opt_params, opt_contentType) {
            var params = opt_params || {};
            makeXhrRequest(relativeUrl, relativeUrl, callback, params.POST_DATA, params.METHOD, params, processNonProxiedResponse, opt_contentType);
        },
        clearOAuthState: function () {
            oauthState = undefined;
        },
        encodeValues: function (fields, opt_noEscaping) {
            var escape = !opt_noEscaping;
            var buf = [];
            var first = false;
            for (var i in fields) {
                if (fields.hasOwnProperty(i) && !/___$/.test(i)) {
                    if (!first) {
                        first = true;
                    } else {
                        buf.push("&");
                    }
                    buf.push(escape ? encodeURIComponent(i) : i);
                    buf.push("=");
                    buf.push(escape ? encodeURIComponent(fields[i]) : fields[i]);
                }
            }
            return buf.join("");
        },
        getProxyUrl: function (url, opt_params) {
            var params = opt_params || {};
            var refresh = params.REFRESH_INTERVAL;
            if (refresh === undefined) {
                refresh = "3600";
            }
            var urlParams = gadgets.util.getUrlParameters();
            var rewriteMimeParam = params.rewriteMime ? "&rewriteMime=" + encodeURIComponent(params.rewriteMime) : "";
            var ret = config.proxyUrl.replace("%url%", encodeURIComponent(url)).replace("%host%", document.location.host).replace("%rawurl%", url).replace("%refresh%", encodeURIComponent(refresh)).replace("%gadget%", encodeURIComponent(urlParams.url)).replace("%container%", encodeURIComponent(urlParams.container || urlParams.synd || "default")).replace("%rewriteMime%", rewriteMimeParam);
            if (ret.indexOf('//') == 0) {
                ret = window.location.protocol + ret;
            }
            return ret;
        }
    };
}();
gadgets.io.RequestParameters = gadgets.util.makeEnum(["METHOD", "CONTENT_TYPE", "POST_DATA", "HEADERS", "AUTHORIZATION", "NUM_ENTRIES", "GET_SUMMARIES", "GET_FULL_HEADERS", "REFRESH_INTERVAL", "OAUTH_SERVICE_NAME", "OAUTH_USE_TOKEN", "OAUTH_TOKEN_NAME", "OAUTH_REQUEST_TOKEN", "OAUTH_REQUEST_TOKEN_SECRET", "OAUTH_RECEIVED_CALLBACK"]);
gadgets.io.MethodType = gadgets.util.makeEnum(["GET", "POST", "PUT", "DELETE", "HEAD"]);
gadgets.io.ContentType = gadgets.util.makeEnum(["TEXT", "DOM", "JSON", "FEED"]);
gadgets.io.AuthorizationType = gadgets.util.makeEnum(["NONE", "SIGNED", "OAUTH"]);
var tamings___ = tamings___ || [];
tamings___.push(function (imports) {
    caja___.whitelistFuncs([
        [gadgets.io, 'encodeValues'],
        [gadgets.io, 'getProxyUrl'],
        [gadgets.io, 'makeRequest']
    ]);
});
var gadgets;
var JSON = window.JSON || gadgets.json;
var _IG_Prefs = (function () {
    var instance = null;
    var _IG_Prefs = function () {
        if (!instance) {
            instance = new gadgets.Prefs();
            instance.setDontEscape_();
        }
        return instance;
    };
    _IG_Prefs._parseURL = gadgets.Prefs.parseUrl;
    return _IG_Prefs;
})();

function _IG_Fetch_wrapper(callback, obj) {
    callback(obj.data ? obj.data : "");
}

function _IG_FetchContent(url, callback, opt_params) {
    var params = opt_params || {};
    if (params.refreshInterval) {
        params['REFRESH_INTERVAL'] = params.refreshInterval;
    } else {
        params['REFRESH_INTERVAL'] = 3600;
    }
    for (var param in params) {
        var pvalue = params[param];
        delete params[param];
        params[param.toUpperCase()] = pvalue;
    }
    var cb = gadgets.util.makeClosure(null, _IG_Fetch_wrapper, callback);
    gadgets.io.makeRequest(url, cb, params);
}

function _IG_FetchXmlContent(url, callback, opt_params) {
    var params = opt_params || {};
    if (params.refreshInterval) {
        params['REFRESH_INTERVAL'] = params.refreshInterval;
    } else {
        params['REFRESH_INTERVAL'] = 3600;
    }
    params.CONTENT_TYPE = "DOM";
    var cb = gadgets.util.makeClosure(null, _IG_Fetch_wrapper, callback);
    gadgets.io.makeRequest(url, cb, params);
}

function _IG_FetchFeedAsJSON(url, callback, numItems, getDescriptions, opt_params) {
    var params = opt_params || {};
    params.CONTENT_TYPE = "FEED";
    params.NUM_ENTRIES = numItems;
    params.GET_SUMMARIES = getDescriptions;
    gadgets.io.makeRequest(url, function (resp) {
        resp.data = resp.data || {};
        if (resp.errors && resp.errors.length > 0) {
            resp.data.ErrorMsg = resp.errors[0];
        }
        if (resp.data.link) {
            resp.data.URL = url;
        }
        if (resp.data.title) {
            resp.data.Title = resp.data.title;
        }
        if (resp.data.description) {
            resp.data.Description = resp.data.description;
        }
        if (resp.data.link) {
            resp.data.Link = resp.data.link;
        }
        if (resp.data.items && resp.data.items.length > 0) {
            resp.data.Entry = resp.data.items;
            for (var index = 0; index < resp.data.Entry.length; ++index) {
                var entry = resp.data.Entry[index];
                entry.Title = entry.title;
                entry.Link = entry.link;
                entry.Summary = entry.summary || entry.description;
                entry.Date = entry.pubDate;
            }
        }
        for (var ix = 0; ix < resp.data.Entry.length; ++ix) {
            var entry = resp.data.Entry[ix];
            entry.Date = (entry.Date / 1000);
        }
        callback(resp.data);
    }, params);
}

function _IG_GetCachedUrl(url, opt_params) {
    var params = opt_params || {};
    params['REFRESH_INTERVAL'] = 3600;
    if (params.refreshInterval) {
        params['REFRESH_INTERVAL'] = params.refreshInterval;
    }
    return gadgets.io.getProxyUrl(url, params);
}

function _IG_GetImageUrl(url, opt_params) {
    return _IG_GetCachedUrl(url, opt_params);
}

function _IG_GetImage(url) {
    var img = document.createElement('img');
    img.src = _IG_GetCachedUrl(url);
    return img;
}

function _IG_RegisterOnloadHandler(callback) {
    gadgets.util.registerOnLoadHandler(callback);
}

function _IG_Callback(handler_func, var_args) {
    var orig_args = arguments;
    return function () {
        var combined_args = Array.prototype.slice.call(arguments);
        handler_func.apply(null, combined_args.concat(Array.prototype.slice.call(orig_args, 1)));
    };
}
var _args = gadgets.util.getUrlParameters;

function _gel(el) {
    return document.getElementById ? document.getElementById(el) : null;
}

function _gelstn(tag) {
    if (tag === "*" && document.all) {
        return document.all;
    }
    return document.getElementsByTagName ? document.getElementsByTagName(tag) : [];
}

function _gelsbyregex(tagName, regex) {
    var matchingTags = _gelstn(tagName);
    var matchingRegex = [];
    for (var i = 0, j = matchingTags.length; i < j; ++i) {
        if (regex.test(matchingTags[i].id)) {
            matchingRegex.push(matchingTags[i]);
        }
    }
    return matchingRegex;
}

function _esc(str) {
    return window.encodeURIComponent ? encodeURIComponent(str) : escape(str);
}

function _unesc(str) {
    return window.decodeURIComponent ? decodeURIComponent(str) : unescape(str);
}

function _hesc(str) {
    return gadgets.util.escapeString(str);
}

function _striptags(str) {
    return str.replace(/<\/?[^>]+>/g, "");
}

function _trim(str) {
    return str.replace(/^\s+|\s+$/g, "");
}

function _toggle(el) {
    el = (typeof el === "string") ? _gel(el) : el;
    if (el !== null) {
        if (el.style.display.length === 0 || el.style.display === "block") {
            el.style.display = "none";
        } else if (el.style.display === "none") {
            el.style.display = "block";
        }
    }
}
var _uid = (function () {
    var _legacy_uidCounter = 0;
    return function () {
        return _legacy_uidCounter++;
    };
})();

function _min(a, b) {
    return (a < b ? a : b);
}

function _max(a, b) {
    return (a > b ? a : b);
}

function _exportSymbols(name, sym) {
    var attach = window;
    var parts = name.split(".");
    for (var i = 0, j = parts.length; i < j; i++) {
        var part = parts[i];
        attach[part] = attach[part] || {};
        attach = attach[part];
    }
    for (var k = 0, l = sym.length; k < l; k += 2) {
        attach[sym[k]] = sym[k + 1];
    }
}

function _IG_AddDOMEventHandler(src, etype, func) {
    gadgets.warn("_IG_AddDOMEventHandler not implemented - see SHINDIG-198");
}
gadgets.window = gadgets.window || {};
(function () {
    gadgets.window.getViewportDimensions = function () {
        var x = 0;
        var y = 0;
        if (self.innerHeight) {
            x = self.innerWidth;
            y = self.innerHeight;
        } else if (document.documentElement && document.documentElement.clientHeight) {
            x = document.documentElement.clientWidth;
            y = document.documentElement.clientHeight;
        } else if (document.body) {
            x = document.body.clientWidth;
            y = document.body.clientHeight;
        }
        return {
            width: x,
            height: y
        };
    };
})();
gadgets.flash = gadgets.flash || {};
gadgets.flash.getMajorVersion = function () {
    var flashMajorVersion = 0;
    if (navigator.plugins && navigator.mimeTypes && navigator.mimeTypes.length) {
        var i = navigator.plugins["Shockwave Flash"];
        if (i && i.description) {
            flashMajorVersion = parseInt(i.description.match(/[0-9]+/)[0], 10);
        }
    } else {
        for (var version = 10; version > 0; version--) {
            try {
                var dummy = new ActiveXObject("ShockwaveFlash.ShockwaveFlash." + version);
                return version;
            } catch (e) {}
        }
    }
    return flashMajorVersion;
};
gadgets.flash.swfContainerId_ = 0;
gadgets.flash.embedFlash = function (swfUrl, swfContainer, swfVersion, opt_params) {
    switch (typeof swfContainer) {
    case 'string':
        swfContainer = document.getElementById(swfContainer);
    case 'object':
        if (swfContainer && (typeof swfContainer.innerHTML === 'string')) {
            break;
        }
    default:
        return false;
    }
    switch (typeof opt_params) {
    case 'undefined':
        opt_params = {};
    case 'object':
        break;
    default:
        return false;
    }
    if (swfUrl.indexOf('//') == 0) {
        swfUrl = document.location.protocol + swfUrl;
    }
    var ver = gadgets.flash.getMajorVersion();
    if (ver) {
        var swfVer = parseInt(swfVersion, 10);
        if (isNaN(swfVer)) {
            swfVer = 0;
        }
        if (ver >= swfVer) {
            if (opt_params.width === void 0) {
                opt_params.width = '100%';
            }
            if (opt_params.height === void 0) {
                opt_params.height = '100%';
            }
            if (typeof opt_params.base !== 'string') {
                var a = document.createElement('a');
                a.href = swfUrl;
                opt_params.base = a.href.match(/^(.*\/)[^\/]*$/)[1];
            }
            if (typeof opt_params.wmode !== 'string') {
                opt_params.wmode = 'opaque';
            }
            while (!opt_params.id) {
                var newId = 'swfContainer' + gadgets.flash.swfContainerId_++;
                if (!document.getElementById(newId)) {
                    opt_params.id = newId;
                }
            }
            var flashObj;
            if (navigator.plugins && navigator.mimeTypes && navigator.mimeTypes.length) {
                opt_params.type = 'application/x-shockwave-flash';
                opt_params.src = swfUrl;
                flashObj = document.createElement('embed');
                for (var prop in opt_params) {
                    if (!/^swf_/.test(prop) && !/___$/.test(prop)) {
                        flashObj.setAttribute(prop, opt_params[prop]);
                    }
                }
                swfContainer.innerHTML = '';
                swfContainer.appendChild(flashObj);
                return true;
            } else {
                var propIsHtmlSafe = function (val) {
                    return !/["<>]/.test(val);
                };
                opt_params.movie = swfUrl;
                var attr = {
                    width: opt_params.width,
                    height: opt_params.height,
                    classid: "clsid:D27CDB6E-AE6D-11CF-96B8-444553540000"
                };
                if (opt_params.id) {
                    attr.id = opt_params.id;
                }
                var html = '<object';
                for (var attrProp in attr) {
                    if (!/___$/.test(attrProp) && propIsHtmlSafe(attrProp) && propIsHtmlSafe(attr[attrProp])) {
                        html += ' ' + attrProp + '="' + attr[attrProp] + '"';
                    }
                }
                html += '>';
                for (var paramsProp in opt_params) {
                    var param = document.createElement('param');
                    if (!/^swf_/.test(paramsProp) && !attr[paramsProp] && !/___$/.test(paramsProp) && propIsHtmlSafe(paramsProp) && propIsHtmlSafe(opt_params[paramsProp])) {
                        html += '<param name="' + paramsProp + '" value="' + opt_params[paramsProp] + '" />';
                    }
                }
                html += '</object>';
            }
            swfContainer.innerHTML = html;
            return true;
        }
    }
    return false;
};
gadgets.flash.embedCachedFlash = function (swfUrl, swfContainer, swfVersion, opt_params) {
    var url = gadgets.io.getProxyUrl(swfUrl, {
        rewriteMime: "application/x-shockwave-flash"
    });
    return gadgets.flash.embedFlash(url, swfContainer, swfVersion, opt_params);
};
var _IG_GetFlashMajorVersion = gadgets.flash.getMajorVersion;
var _IG_EmbedFlash = function (swfUrl, swfContainer, opt_params) {
    return gadgets.flash.embedFlash(swfUrl, swfContainer, opt_params.swf_version, opt_params);
};
var _IG_EmbedCachedFlash = function (swfUrl, swfContainer, opt_params) {
    return gadgets.flash.embedCachedFlash(swfUrl, swfContainer, opt_params.swf_version, opt_params);
};
var tamings___ = tamings___ || [];
var bridge___;
tamings___.push(function (imports) {
    ___.tamesTo(gadgets.flash.embedFlash, (function () {
        var cleanse = (function () {
            var ifr = document.createElement("iframe");
            ifr.width = 1;
            ifr.height = 1;
            ifr.border = 0;
            document.body.appendChild(ifr);
            var O = ifr.contentWindow.Object;
            document.body.removeChild(ifr);
            var c = function (obj) {
                var t = typeof obj,
                    i;
                if (t === 'number' || t === 'boolean' || t === 'string') {
                    return obj;
                }
                if (t === 'object') {
                    var o = new O;
                    for (i in obj) {
                        if (/__$/.test(i)) {
                            continue;
                        }
                        o[i] = c(obj[i]);
                    }
                    if (obj.length !== undefined) {
                        o.length = obj.length;
                    }
                    return o;
                }
                return (void 0);
            };
            return c;
        })();
        var d = document.createElement('div');
        d.appendChild(document.createTextNode("bridge"));
        document.body.appendChild(d);
        gadgets.flash.embedFlash("/container/Bridge.swf", d, 10, {
            allowNetworking: "always",
            allowScriptAccess: "all",
            width: 0,
            height: 0,
            flashvars: "logging=true"
        });
        bridge___ = d.childNodes[0];
        bridge___.channels = [];
        callJS = function (functionName, argv) {
            var $v = ___.getNewModuleHandler().getImports().$v;
            return $v.cf($v.ro(functionName), argv);
        };
        onFlashBridgeReady = function () {
            var len = bridge___.channels.length;
            for (var i = 0; i < len; ++i) {
                bridge___.registerChannel(bridge___.channels[i]);
            }
            delete bridge___.channels;
            var outers = ___.getNewModuleHandler().getImports().$v.getOuters();
            if (outers.onFlashBridgeReady) {
                callJS("onFlashBridgeReady", []);
            }
        };
        return ___.frozenFunc(function tamedEmbedFlash(swfUrl, swfContainer, swfVersion, opt_params) {
            if (typeof swfContainer === "string") {
                var $v = ___.getNewModuleHandler().getImports().$v;
                swfContainer = $v.cm($v.ro("document"), "getElementById", [swfContainer]);
            } else if (typeof swfContainer !== "object" || !swfContainer.node___) {
                return false;
            }
            var channel = "_flash" + ("" + Math.random()).substring(2);
            var new_params = {};
            for (i in opt_params) {
                if (i.match(/___$/)) {
                    continue;
                }
                var ilc = i.toLowerCase();
                if (ilc === "allownetworking" || ilc === "allowscriptaccess") {
                    continue;
                }
                var topi = typeof opt_params[i];
                if (topi !== "string" && topi !== "number") {
                    continue;
                }
                new_params[i] = opt_params[i];
            }
            new_params.allowNetworking = "never";
            new_params.allowScriptAccess = "none";
            if (!new_params.flashVars) {
                new_params.flashVars = "";
            }
            new_params.flashVars += "&channel=" + channel;
            gadgets.flash.embedFlash(swfUrl, swfContainer.node___, 10, new_params);
            if (bridge___.channels) {
                bridge___.channels.push(channel);
            } else {
                bridge___.registerChannel(channel);
            }
            return ___.primFreeze({
                callSWF: (function (channel) {
                    return ___.func(function (methodName, argv) {
                        return bridge___.callSWF("" + channel, "" + methodName, cleanse(argv));
                    });
                })(channel)
            });
        });
    })());
});
var opensocial = opensocial || {};
opensocial.requestSendMessage = function (recipients, message, opt_callback, opt_params) {
    return opensocial.Container.get().requestSendMessage(recipients, message, opt_callback, opt_params);
};
opensocial.requestShareApp = function (recipients, reason, opt_callback, opt_params) {
    opensocial.Container.get().requestShareApp(recipients, reason, opt_callback, opt_params);
};
opensocial.requestCreateActivity = function (activity, priority, opt_callback) {
    if (!activity || (!activity.getField(opensocial.Activity.Field.TITLE) && !activity.getField(opensocial.Activity.Field.TITLE_ID))) {
        if (opt_callback) {
            window.setTimeout(function () {
                opt_callback(new opensocial.ResponseItem(null, null, opensocial.ResponseItem.Error.BAD_REQUEST, "You must pass in an activity with a title or title id."));
            }, 0);
        }
        return;
    }
    opensocial.Container.get().requestCreateActivity(activity, priority, opt_callback);
};
opensocial.CreateActivityPriority = {
    HIGH: 'HIGH',
    LOW: 'LOW'
};
opensocial.hasPermission = function (permission) {
    return opensocial.Container.get().hasPermission(permission);
};
opensocial.requestPermission = function (permissions, reason, opt_callback) {
    opensocial.Container.get().requestPermission(permissions, reason, opt_callback);
};
opensocial.Permission = {
    VIEWER: 'viewer'
};
opensocial.getEnvironment = function () {
    return opensocial.Container.get().getEnvironment();
};
opensocial.newDataRequest = function () {
    return opensocial.Container.get().newDataRequest();
};
opensocial.newActivity = function (params) {
    return opensocial.Container.get().newActivity(params);
};
opensocial.newAlbum = function (opt_params) {
    return opensocial.Container.get().newAlbum(opt_params);
};
opensocial.newMediaItem = function (mimeType, url, opt_params) {
    return opensocial.Container.get().newMediaItem(mimeType, url, opt_params);
};
opensocial.newMessage = function (body, opt_params) {
    return opensocial.Container.get().newMessage(body, opt_params);
};
opensocial.EscapeType = {
    HTML_ESCAPE: 'htmlEscape',
    NONE: 'none'
};
opensocial.newIdSpec = function (params) {
    return opensocial.Container.get().newIdSpec(params);
};
opensocial.newNavigationParameters = function (params) {
    return opensocial.Container.get().newNavigationParameters(params);
};
opensocial.invalidateCache = function () {
    opensocial.Container.get().invalidateCache();
};
Function.prototype.inherits = function (parentCtor) {
    function tempCtor() {}
    tempCtor.prototype = parentCtor.prototype;
    this.superClass_ = parentCtor.prototype;
    this.prototype = new tempCtor();
    this.prototype.constructor = this;
};
opensocial.Activity = function (params) {
    this.fields_ = params;
};
opensocial.Activity.Field = {
    TITLE_ID: 'titleId',
    TITLE: 'title',
    TEMPLATE_PARAMS: 'templateParams',
    URL: 'url',
    MEDIA_ITEMS: 'mediaItems',
    BODY_ID: 'bodyId',
    BODY: 'body',
    EXTERNAL_ID: 'externalId',
    STREAM_TITLE: 'streamTitle',
    STREAM_URL: 'streamUrl',
    STREAM_SOURCE_URL: 'streamSourceUrl',
    STREAM_FAVICON_URL: 'streamFaviconUrl',
    PRIORITY: 'priority',
    ID: 'id',
    USER_ID: 'userId',
    APP_ID: 'appId',
    POSTED_TIME: 'postedTime'
};
opensocial.Activity.prototype.getId = function () {
    return this.getField(opensocial.Activity.Field.ID);
};
opensocial.Activity.prototype.getField = function (key, opt_params) {
    return opensocial.Container.getField(this.fields_, key, opt_params);
};
opensocial.Activity.prototype.setField = function (key, data) {
    return (this.fields_[key] = data);
};
opensocial.Address = function (opt_params) {
    this.fields_ = opt_params || {};
};
opensocial.Address.Field = {
    TYPE: 'type',
    UNSTRUCTURED_ADDRESS: 'unstructuredAddress',
    PO_BOX: 'poBox',
    STREET_ADDRESS: 'streetAddress',
    EXTENDED_ADDRESS: 'extendedAddress',
    REGION: 'region',
    LOCALITY: 'locality',
    POSTAL_CODE: 'postalCode',
    COUNTRY: 'country',
    LATITUDE: 'latitude',
    LONGITUDE: 'longitude'
};
opensocial.Address.prototype.getField = function (key, opt_params) {
    return opensocial.Container.getField(this.fields_, key, opt_params);
};
opensocial.Album = function (opt_params) {
    this.fields_ = opt_params || {};
};
opensocial.Album.Field = {
    DESCRIPTION: 'description',
    ID: 'id',
    LOCATION: 'location',
    MEDIA_ITEM_COUNT: 'mediaITemCount',
    MEDIA_MIME_TYPE: 'MEDIA_MIME_TYPE',
    MEDIA_TYPE: 'MEDIA_TYPE',
    OWNER_ID: 'ownerId',
    THUMBNAIL_URL: 'thumbnailUrl',
    TITLE: 'title'
};
opensocial.Album.prototype.getField = function (key, opt_params) {
    return opensocial.Container.getField(this.fields_, key, opt_params);
};
opensocial.Album.prototype.setField = function (key, data) {
    return this.fields_[key] = data;
};
opensocial.BodyType = function (opt_params) {
    this.fields_ = opt_params || {};
};
opensocial.BodyType.Field = {
    BUILD: 'build',
    HEIGHT: 'height',
    WEIGHT: 'weight',
    EYE_COLOR: 'eyeColor',
    HAIR_COLOR: 'hairColor'
};
opensocial.BodyType.prototype.getField = function (key, opt_params) {
    return opensocial.Container.getField(this.fields_, key, opt_params);
};
opensocial.Collection = function (array, opt_offset, opt_totalSize) {
    this.array_ = array || [];
    this.offset_ = opt_offset || 0;
    this.totalSize_ = opt_totalSize || this.array_.length;
};
opensocial.Collection.prototype.getById = function (id) {
    for (var i = 0; i < this.size(); i++) {
        var item = this.array_[i];
        if (item.getId() === id) {
            return item;
        }
    }
    return null;
};
opensocial.Collection.prototype.size = function () {
    return this.array_.length;
};
opensocial.Collection.prototype.each = function (fn) {
    for (var i = 0; i < this.size(); i++) {
        fn(this.array_[i]);
    }
};
opensocial.Collection.prototype.asArray = function () {
    return this.array_;
};
opensocial.Collection.prototype.getTotalSize = function () {
    return this.totalSize_;
};
opensocial.Collection.prototype.getOffset = function () {
    return this.offset_;
};
opensocial.Container = function () {};
opensocial.Container.container_ = null;
opensocial.Container.setContainer = function (container) {
    opensocial.Container.container_ = container;
};
opensocial.Container.get = function () {
    return opensocial.Container.container_;
};
opensocial.Container.prototype.getEnvironment = function () {};
opensocial.Container.prototype.requestSendMessage = function (recipients, message, opt_callback, opt_params) {
    gadgets.rpc.call(null, "requestSendMessage", opt_callback, recipients, message, opt_callback, opt_params);
};
opensocial.Container.prototype.requestShareApp = function (recipients, reason, opt_callback, opt_params) {
    if (opt_callback) {
        window.setTimeout(function () {
            opt_callback(new opensocial.ResponseItem(null, null, opensocial.ResponseItem.Error.NOT_IMPLEMENTED, null));
        }, 0);
    }
};
opensocial.Container.prototype.requestCreateActivity = function (activity, priority, opt_callback) {
    if (opt_callback) {
        window.setTimeout(function () {
            opt_callback(new opensocial.ResponseItem(null, null, opensocial.ResponseItem.Error.NOT_IMPLEMENTED, null));
        }, 0);
    }
};
opensocial.Container.prototype.hasPermission = function (permission) {
    return false;
};
opensocial.Container.prototype.requestPermission = function (permissions, reason, opt_callback) {
    if (opt_callback) {
        window.setTimeout(function () {
            opt_callback(new opensocial.ResponseItem(null, null, opensocial.ResponseItem.Error.NOT_IMPLEMENTED, null));
        }, 0);
    }
};
opensocial.Container.prototype.requestData = function (dataRequest, callback) {};
opensocial.Container.prototype.newCreateAlbumRequest = function (idSpec, album) {};
opensocial.Container.prototype.newCreateMediaItemRequest = function (idSpec, albumId, mediaItem) {};
opensocial.Container.prototype.newDeleteAlbumRequest = function (idSpec, albumId) {};
opensocial.Container.prototype.newFetchPersonRequest = function (id, opt_params) {};
opensocial.Container.prototype.newFetchPeopleRequest = function (idSpec, opt_params) {};
opensocial.Container.prototype.newFetchPersonAppDataRequest = function (idSpec, keys, opt_params) {};
opensocial.Container.prototype.newUpdatePersonAppDataRequest = function (key, value) {};
opensocial.Container.prototype.newRemovePersonAppDataRequest = function (keys) {};
opensocial.Container.prototype.newUpdateAlbumRequest = function (idSpec, albumId, opt_params) {};
opensocial.Container.prototype.newUpdateMediaItemRequest = function (idSpec, albumId, mediaItemId, opt_params) {};
opensocial.Container.prototype.newFetchActivitiesRequest = function (idSpec, opt_params) {};
opensocial.Container.prototype.newFetchAlbumsRequest = function (idSpec, opt_params) {};
opensocial.Container.prototype.newFetchMessageCollectionsRequest = function (idSpec, opt_params) {};
opensocial.Container.prototype.newFetchMessagesRequest = function (idSpec, msgCollId, opt_params) {};
opensocial.Container.prototype.newCollection = function (array, opt_offset, opt_totalSize) {
    return new opensocial.Collection(array, opt_offset, opt_totalSize);
};
opensocial.Container.prototype.newPerson = function (opt_params, opt_isOwner, opt_isViewer) {
    return new opensocial.Person(opt_params, opt_isOwner, opt_isViewer);
};
opensocial.Container.prototype.newActivity = function (opt_params) {
    return new opensocial.Activity(opt_params);
};
opensocial.Container.prototype.newAlbum = function (opt_params) {
    return new opensocial.Album(opt_params);
};
opensocial.Container.prototype.newMediaItem = function (mimeType, url, opt_params) {
    return new opensocial.MediaItem(mimeType, url, opt_params);
};
opensocial.Container.prototype.newMessage = function (body, opt_params) {
    return new opensocial.Message(body, opt_params);
};
opensocial.Container.prototype.newIdSpec = function (params) {
    return new opensocial.IdSpec(params);
};
opensocial.Container.prototype.newNavigationParameters = function (params) {
    return new opensocial.NavigationParameters(params);
};
opensocial.Container.prototype.newResponseItem = function (originalDataRequest, data, opt_errorCode, opt_errorMessage) {
    return new opensocial.ResponseItem(originalDataRequest, data, opt_errorCode, opt_errorMessage);
};
opensocial.Container.prototype.newDataResponse = function (responseItems, opt_globalError) {
    return new opensocial.DataResponse(responseItems, opt_globalError);
};
opensocial.Container.prototype.newDataRequest = function () {
    return new opensocial.DataRequest();
};
opensocial.Container.prototype.newEnvironment = function (domain, supportedFields) {
    return new opensocial.Environment(domain, supportedFields);
};
opensocial.Container.prototype.invalidateCache = function () {};
opensocial.Container.isArray = function (val) {
    return val instanceof Array;
};
opensocial.Container.getField = function (fields, key, opt_params) {
    var value = fields[key];
    return opensocial.Container.escape(value, opt_params, false);
};
opensocial.Container.escape = function (value, opt_params, opt_escapeObjects) {
    if (opt_params && opt_params[opensocial.DataRequest.DataRequestFields.ESCAPE_TYPE] == opensocial.EscapeType.NONE) {
        return value;
    } else {
        return gadgets.util.escape(value, opt_escapeObjects);
    }
};
opensocial.DataRequest = function () {
    this.requestObjects_ = [];
};
opensocial.DataRequest.prototype.requestObjects_ = null;
opensocial.DataRequest.prototype.getRequestObjects = function () {
    return this.requestObjects_;
};
opensocial.DataRequest.prototype.add = function (request, opt_key) {
    return this.requestObjects_.push({
        'key': opt_key,
        'request': request
    });
};
opensocial.DataRequest.prototype.send = function (opt_callback) {
    var callback = opt_callback || function () {};
    opensocial.Container.get().requestData(this, callback);
};
opensocial.DataRequest.SortOrder = {
    TOP_FRIENDS: 'topFriends',
    NAME: 'name'
};
opensocial.DataRequest.FilterType = {
    ALL: 'all',
    HAS_APP: 'hasApp',
    TOP_FRIENDS: 'topFriends',
    IS_FRIENDS_WITH: 'isFriendsWith'
};
opensocial.DataRequest.PeopleRequestFields = {
    PROFILE_DETAILS: 'profileDetail',
    SORT_ORDER: 'sortOrder',
    FILTER: 'filter',
    FILTER_OPTIONS: 'filterOptions',
    FIRST: 'first',
    MAX: 'max',
    APP_DATA: 'appData',
    ESCAPE_TYPE: 'escapeType'
};
opensocial.DataRequest.prototype.addDefaultParam = function (params, name, defaultValue) {
    params[name] = params[name] || defaultValue;
};
opensocial.DataRequest.prototype.addDefaultProfileFields = function (params) {
    var fields = opensocial.DataRequest.PeopleRequestFields;
    var profileFields = params[fields.PROFILE_DETAILS] || [];
    params[fields.PROFILE_DETAILS] = profileFields.concat([opensocial.Person.Field.ID, opensocial.Person.Field.NAME, opensocial.Person.Field.THUMBNAIL_URL]);
};
opensocial.DataRequest.prototype.asArray = function (keys) {
    if (opensocial.Container.isArray(keys)) {
        return keys;
    } else {
        return [keys];
    }
};
opensocial.DataRequest.prototype.newCreateAlbumRequest = function (idSpec, album) {
    return opensocial.Container.get().newCreateAlbumRequest(idSpec, album);
};
opensocial.DataRequest.prototype.newCreateMediaItemRequest = function (idSpec, albumId, mediaItem) {
    return opensocial.Container.get().newCreateMediaItemRequest(idSpec, albumId, mediaItem)
};
opensocial.DataRequest.prototype.newDeleteAlbumRequest = function (idSpec, albumId) {
    return opensocial.Container.get().newDeleteAlbumRequest(idSpec, albumId);
};
opensocial.DataRequest.prototype.newFetchPersonRequest = function (id, opt_params) {
    opt_params = opt_params || {};
    this.addDefaultProfileFields(opt_params);
    return opensocial.Container.get().newFetchPersonRequest(id, opt_params);
};
opensocial.DataRequest.prototype.newFetchPeopleRequest = function (idSpec, opt_params) {
    opt_params = opt_params || {};
    var fields = opensocial.DataRequest.PeopleRequestFields;
    this.addDefaultProfileFields(opt_params);
    this.addDefaultParam(opt_params, fields.SORT_ORDER, opensocial.DataRequest.SortOrder.TOP_FRIENDS);
    this.addDefaultParam(opt_params, fields.FILTER, opensocial.DataRequest.FilterType.ALL);
    this.addDefaultParam(opt_params, fields.FIRST, 0);
    this.addDefaultParam(opt_params, fields.MAX, 20);
    return opensocial.Container.get().newFetchPeopleRequest(idSpec, opt_params);
};
opensocial.DataRequest.AlbumRequestFields = {
    FIRST: 'first',
    MAX: 'max'
};
opensocial.DataRequest.DataRequestFields = {
    ESCAPE_TYPE: 'escapeType'
};
opensocial.DataRequest.prototype.newFetchPersonAppDataRequest = function (idSpec, keys, opt_params) {
    return opensocial.Container.get().newFetchPersonAppDataRequest(idSpec, this.asArray(keys), opt_params);
};
opensocial.DataRequest.prototype.newUpdateAlbumRequest = function (idSpec, albumId, opt_params) {
    return opensocial.Container.get().newUpdateAlbumRequest(idSpec, albumId, opt_params);
};
opensocial.DataRequest.prototype.newUpdateMediaItemRequest = function (idSpec, albumId, mediaItemId, opt_params) {
    return opensocial.Container.get().newUpdateMediaItemRequest(idSpec, albumId, mediaItemId, opt_params);
};
opensocial.DataRequest.prototype.newUpdatePersonAppDataRequest = function (key, value) {
    return opensocial.Container.get().newUpdatePersonAppDataRequest(key, value);
};
opensocial.DataRequest.prototype.newRemovePersonAppDataRequest = function (keys) {
    return opensocial.Container.get().newRemovePersonAppDataRequest(keys);
};
opensocial.DataRequest.ActivityRequestFields = {
    APP_ID: 'appId',
    FIRST: 'first',
    MAX: 'max'
};
opensocial.DataRequest.prototype.newFetchActivitiesRequest = function (idSpec, opt_params) {
    opt_params = opt_params || {};
    var fields = opensocial.DataRequest.ActivityRequestFields;
    this.addDefaultParam(opt_params, fields.FIRST, 0);
    this.addDefaultParam(opt_params, fields.MAX, 20);
    return opensocial.Container.get().newFetchActivitiesRequest(idSpec, opt_params);
};
opensocial.DataRequest.prototype.newFetchAlbumsRequest = function (idSpec, opt_params) {
    opt_params = opt_params || {};
    return opensocial.Container.get().newFetchAlbumsRequest(idSpec, opt_params);
};
opensocial.DataRequest.prototype.newFetchMessageCollectionsRequest = function (idSpec, opt_params) {
    opt_params = opt_params || {};
    return opensocial.Container.get().newFetchMessageCollectionsRequest(idSpec, opt_params);
};
opensocial.DataRequest.prototype.newFetchMessagesRequest = function (idSpec, msgCollId, opt_params) {
    opt_params = opt_params || {};
    return opensocial.Container.get().newFetchMessagesRequest(idSpec, msgCollId, opt_params);
};
opensocial.DataResponse = function (responseItems, opt_globalError, opt_errorMessage) {
    this.responseItems_ = responseItems;
    this.globalError_ = opt_globalError;
    this.errorMessage_ = opt_errorMessage;
};
opensocial.DataResponse.prototype.hadError = function () {
    return !!this.globalError_;
};
opensocial.DataResponse.prototype.getErrorMessage = function () {
    return this.errorMessage_;
};
opensocial.DataResponse.prototype.get = function (key) {
    return this.responseItems_[key];
};
opensocial.Email = function (opt_params) {
    this.fields_ = opt_params || {};
};
opensocial.Email.Field = {
    TYPE: 'type',
    ADDRESS: 'address'
};
opensocial.Email.prototype.getField = function (key, opt_params) {
    return opensocial.Container.getField(this.fields_, key, opt_params);
};
opensocial.Enum = function (key, displayValue) {
    this.key = key;
    this.displayValue = displayValue;
};
opensocial.Enum.prototype.getKey = function () {
    return gadgets.util.escape(this.key);
};
opensocial.Enum.prototype.getDisplayValue = function () {
    return gadgets.util.escape(this.displayValue);
};
opensocial.Enum.Smoker = {
    NO: 'NO',
    YES: 'YES',
    SOCIALLY: 'SOCIALLY',
    OCCASIONALLY: 'OCCASIONALLY',
    REGULARLY: 'REGULARLY',
    HEAVILY: 'HEAVILY',
    QUITTING: 'QUITTING',
    QUIT: 'QUIT'
};
opensocial.Enum.Drinker = {
    NO: 'NO',
    YES: 'YES',
    SOCIALLY: 'SOCIALLY',
    OCCASIONALLY: 'OCCASIONALLY',
    REGULARLY: 'REGULARLY',
    HEAVILY: 'HEAVILY',
    QUITTING: 'QUITTING',
    QUIT: 'QUIT'
};
opensocial.Enum.Gender = {
    MALE: 'MALE',
    FEMALE: 'FEMALE'
};
opensocial.Enum.LookingFor = {
    DATING: 'DATING',
    FRIENDS: 'FRIENDS',
    RELATIONSHIP: 'RELATIONSHIP',
    NETWORKING: 'NETWORKING',
    ACTIVITY_PARTNERS: 'ACTIVITY_PARTNERS',
    RANDOM: 'RANDOM'
};
opensocial.Enum.Presence = {
    AWAY: 'AWAY',
    CHAT: 'CHAT',
    DND: 'DND',
    OFFLINE: 'OFFLINE',
    ONLINE: 'ONLINE',
    XA: 'XA'
};
opensocial.Environment = function (domain, supportedFields) {
    this.domain = domain;
    this.supportedFields = supportedFields;
};
opensocial.Environment.prototype.getDomain = function () {
    return this.domain;
};
opensocial.Environment.ObjectType = {
    PERSON: 'person',
    ADDRESS: 'address',
    BODY_TYPE: 'bodyType',
    EMAIL: 'email',
    NAME: 'name',
    ORGANIZATION: 'organization',
    PHONE: 'phone',
    URL: 'url',
    ACTIVITY: 'activity',
    MEDIA_ITEM: 'mediaItem',
    MESSAGE: 'message',
    MESSAGE_TYPE: 'messageType',
    SORT_ORDER: 'sortOrder',
    FILTER_TYPE: 'filterType'
};
opensocial.Environment.prototype.supportsField = function (objectType, fieldName) {
    var supportedObjectFields = this.supportedFields[objectType] || [];
    return !!supportedObjectFields[fieldName];
};
opensocial.IdSpec = function (opt_params) {
    this.fields_ = opt_params || {};
};
opensocial.IdSpec.Field = {
    USER_ID: 'userId',
    GROUP_ID: 'groupId',
    NETWORK_DISTANCE: 'networkDistance'
};
opensocial.IdSpec.PersonId = {
    OWNER: 'OWNER',
    VIEWER: 'VIEWER'
};
opensocial.IdSpec.GroupId = {
    SELF: 'SELF',
    FRIENDS: 'FRIENDS',
    ALL: 'ALL'
};
opensocial.IdSpec.prototype.getField = function (key, opt_params) {
    return opensocial.Container.getField(this.fields_, key, opt_params);
};
opensocial.IdSpec.prototype.setField = function (key, data) {
    return (this.fields_[key] = data);
};
opensocial.MediaItem = function (mimeType, url, opt_params) {
    this.fields_ = {};
    if (opt_params) {
        for (var k in opt_params) {
            if (opt_params.hasOwnProperty(k)) {
                this.fields_[k] = opt_params[k];
            }
        }
    }
    this.fields_[opensocial.MediaItem.Field.MIME_TYPE] = mimeType;
    this.fields_[opensocial.MediaItem.Field.URL] = url;
};
opensocial.MediaItem.Type = {
    IMAGE: 'image',
    VIDEO: 'video',
    AUDIO: 'audio'
};
opensocial.MediaItem.Field = {
    TYPE: 'type',
    MIME_TYPE: 'mimeType',
    URL: 'url'
};
opensocial.MediaItem.prototype.getField = function (key, opt_params) {
    return opensocial.Container.getField(this.fields_, key, opt_params);
};
opensocial.MediaItem.prototype.setField = function (key, data) {
    return (this.fields_[key] = data);
};
opensocial.MessageCollection = function (opt_params) {
    this.fields_ = opt_params || {};
};
opensocial.MessageCollection.Field = {
    ID: 'id',
    TITLE: 'title',
    TOTAL: 'total',
    UNREAD: 'unread',
    UPDATED: 'updated',
    URLS: 'urls'
};
opensocial.MessageCollection.prototype.getField = function (key, opt_params) {
    return opensocial.Container.getField(this.fields_, key, opt_params);
};
opensocial.MessageCollection.prototype.setField = function (key, data) {
    return this.fields_[key] = data;
};
opensocial.Message = function (body_or_params, opt_params) {
    if (typeof body_or_params == 'string') {
        this.fields_ = opt_params || {};
        this.fields_[opensocial.Message.Field.BODY] = body_or_params;
    } else {
        this.fields_ = body_or_params || {};
    }
};
opensocial.Message.Field = {
    APP_URL: 'appUrl',
    BODY: 'body',
    BODY_ID: 'bodyId',
    COLLECTION_IDS: 'collectionIds',
    ID: 'id',
    PARENT_ID: 'parentId',
    RECIPIENTS: 'recipients',
    SENDER_ID: 'senderId',
    STATUS: 'status',
    TIME_SENT: 'timeSent',
    TITLE: 'title',
    TITLE_ID: 'titleId',
    TYPE: 'type',
    UPDATED: 'updated',
    URLS: 'urls'
};
opensocial.Message.Type = {
    EMAIL: 'email',
    NOTIFICATION: 'notification',
    PRIVATE_MESSAGE: 'privateMessage',
    PUBLIC_MESSAGE: 'publicMessage'
};
opensocial.Message.Status = {
    NEW: 'new',
    DELETED: 'deleted',
    FLAGGED: 'flagged'
};
opensocial.Message.prototype.getField = function (key, opt_params) {
    return opensocial.Container.getField(this.fields_, key, opt_params);
};
opensocial.Message.prototype.setField = function (key, data) {
    return (this.fields_[key] = data);
};
opensocial.Name = function (opt_params) {
    this.fields_ = opt_params || {};
};
opensocial.Name.Field = {
    FAMILY_NAME: 'familyName',
    GIVEN_NAME: 'givenName',
    ADDITIONAL_NAME: 'additionalName',
    HONORIFIC_PREFIX: 'honorificPrefix',
    HONORIFIC_SUFFIX: 'honorificSuffix',
    UNSTRUCTURED: 'unstructured'
};
opensocial.Name.prototype.getField = function (key, opt_params) {
    return opensocial.Container.getField(this.fields_, key, opt_params);
};
opensocial.NavigationParameters = function (opt_params) {
    this.fields_ = opt_params || {};
};
opensocial.NavigationParameters.Field = {
    VIEW: 'view',
    OWNER: 'owner',
    PARAMETERS: 'parameters'
};
opensocial.NavigationParameters.prototype.getField = function (key, opt_params) {
    return opensocial.Container.getField(this.fields_, key, opt_params);
};
opensocial.NavigationParameters.prototype.setField = function (key, data) {
    return (this.fields_[key] = data);
};
opensocial.NavigationParameters.DestinationType = {
    VIEWER_DESTINATION: "viewerDestination",
    RECIPIENT_DESTINATION: "recipientDestination"
};
opensocial.Organization = function (opt_params) {
    this.fields_ = opt_params || {};
};
opensocial.Organization.Field = {
    NAME: 'name',
    TITLE: 'title',
    DESCRIPTION: 'description',
    FIELD: 'field',
    SUB_FIELD: 'subField',
    START_DATE: 'startDate',
    END_DATE: 'endDate',
    SALARY: 'salary',
    ADDRESS: 'address',
    WEBPAGE: 'webpage'
};
opensocial.Organization.prototype.getField = function (key, opt_params) {
    return opensocial.Container.getField(this.fields_, key, opt_params);
};
opensocial.Person = function (opt_params, opt_isOwner, opt_isViewer) {
    this.fields_ = opt_params || {};
    this.isOwner_ = opt_isOwner;
    this.isViewer_ = opt_isViewer;
};
opensocial.Person.Field = {
    ID: 'id',
    NAME: 'name',
    NICKNAME: 'nickname',
    THUMBNAIL_URL: 'thumbnailUrl',
    PROFILE_URL: 'profileUrl',
    CURRENT_LOCATION: 'currentLocation',
    ADDRESSES: 'addresses',
    EMAILS: 'emails',
    PHONE_NUMBERS: 'phoneNumbers',
    ABOUT_ME: 'aboutMe',
    STATUS: 'status',
    PROFILE_SONG: 'profileSong',
    PROFILE_VIDEO: 'profileVideo',
    GENDER: 'gender',
    SEXUAL_ORIENTATION: 'sexualOrientation',
    RELATIONSHIP_STATUS: 'relationshipStatus',
    AGE: 'age',
    DATE_OF_BIRTH: 'dateOfBirth',
    BODY_TYPE: 'bodyType',
    ETHNICITY: 'ethnicity',
    SMOKER: 'smoker',
    DRINKER: 'drinker',
    CHILDREN: 'children',
    PETS: 'pets',
    LIVING_ARRANGEMENT: 'livingArrangement',
    TIME_ZONE: 'timeZone',
    LANGUAGES_SPOKEN: 'languagesSpoken',
    JOBS: 'jobs',
    JOB_INTERESTS: 'jobInterests',
    SCHOOLS: 'schools',
    INTERESTS: 'interests',
    URLS: 'urls',
    MUSIC: 'music',
    MOVIES: 'movies',
    TV_SHOWS: 'tvShows',
    BOOKS: 'books',
    ACTIVITIES: 'activities',
    SPORTS: 'sports',
    HEROES: 'heroes',
    QUOTES: 'quotes',
    CARS: 'cars',
    FOOD: 'food',
    TURN_ONS: 'turnOns',
    TURN_OFFS: 'turnOffs',
    TAGS: 'tags',
    ROMANCE: 'romance',
    SCARED_OF: 'scaredOf',
    HAPPIEST_WHEN: 'happiestWhen',
    FASHION: 'fashion',
    HUMOR: 'humor',
    LOOKING_FOR: 'lookingFor',
    RELIGION: 'religion',
    POLITICAL_VIEWS: 'politicalViews',
    HAS_APP: 'hasApp',
    NETWORK_PRESENCE: 'networkPresence'
};
opensocial.Person.prototype.getId = function () {
    return this.getField(opensocial.Person.Field.ID);
};
var ORDERED_NAME_FIELDS_ = [opensocial.Name.Field.HONORIFIC_PREFIX, opensocial.Name.Field.GIVEN_NAME, opensocial.Name.Field.FAMILY_NAME, opensocial.Name.Field.HONORIFIC_SUFFIX, opensocial.Name.Field.ADDITIONAL_NAME];
opensocial.Person.prototype.getDisplayName = function () {
    var name = this.getField(opensocial.Person.Field.NAME);
    if (name) {
        var unstructured = name.getField(opensocial.Name.Field.UNSTRUCTURED);
        if (unstructured) {
            return unstructured;
        }
        var fullName = '';
        for (var i = 0; i < ORDERED_NAME_FIELDS_.length; i++) {
            var nameValue = name.getField(ORDERED_NAME_FIELDS_[i]);
            if (nameValue) {
                fullName += nameValue + ' ';
            }
        }
        return fullName.replace(/^\s+|\s+$/g, '');
    }
    return this.getField(opensocial.Person.Field.NICKNAME);
};
opensocial.Person.prototype.getField = function (key, opt_params) {
    return opensocial.Container.getField(this.fields_, key, opt_params);
};
opensocial.Person.prototype.getAppData = function (key) {};
opensocial.Person.prototype.isViewer = function () {
    return !!this.isViewer_;
};
opensocial.Person.prototype.isOwner = function () {
    return !!this.isOwner_;
};
opensocial.Phone = function (opt_params) {
    this.fields_ = opt_params || {};
};
opensocial.Phone.Field = {
    TYPE: 'type',
    NUMBER: 'number'
};
opensocial.Phone.prototype.getField = function (key, opt_params) {
    return opensocial.Container.getField(this.fields_, key, opt_params);
};
opensocial.ResponseItem = function (originalDataRequest, data, opt_errorCode, opt_errorMessage) {
    this.originalDataRequest_ = originalDataRequest;
    this.data_ = data;
    this.errorCode_ = opt_errorCode;
    this.errorMessage_ = opt_errorMessage;
};
opensocial.ResponseItem.prototype.hadError = function () {
    return !!this.errorCode_;
};
opensocial.ResponseItem.Error = {
    NOT_IMPLEMENTED: 'notImplemented',
    UNAUTHORIZED: 'unauthorized',
    FORBIDDEN: 'forbidden',
    BAD_REQUEST: 'badRequest',
    INTERNAL_ERROR: 'internalError',
    LIMIT_EXCEEDED: 'limitExceeded'
};
opensocial.ResponseItem.prototype.getErrorCode = function () {
    return this.errorCode_;
};
opensocial.ResponseItem.prototype.getErrorMessage = function () {
    return this.errorMessage_;
};
opensocial.ResponseItem.prototype.getOriginalDataRequest = function () {
    return this.originalDataRequest_;
};
opensocial.ResponseItem.prototype.getData = function () {
    return this.data_;
};
opensocial.Url = function (opt_params) {
    this.fields_ = opt_params || {};
};
opensocial.Url.Field = {
    TYPE: 'type',
    LINK_TEXT: 'linkText',
    ADDRESS: 'address'
};
opensocial.Url.prototype.getField = function (key, opt_params) {
    return opensocial.Container.getField(this.fields_, key, opt_params);
};
var tamings___ = tamings___ || [];
tamings___.push(function (imports) {
    ___.grantRead(opensocial, 'CreateActivityPriority');
    ___.grantRead(opensocial, 'EscapeType');
    ___.grantRead(opensocial.Activity, 'Field');
    ___.grantRead(opensocial.Address, 'Field');
    ___.grantRead(opensocial.Album, 'Field');
    ___.grantRead(opensocial.BodyType, 'Field');
    ___.grantRead(opensocial.DataRequest, 'ActivityRequestFields');
    ___.grantRead(opensocial.DataRequest, 'DataRequestFields');
    ___.grantRead(opensocial.DataRequest, 'FilterType');
    ___.grantRead(opensocial.DataRequest, 'Group');
    ___.grantRead(opensocial.DataRequest, 'PeopleRequestFields');
    ___.grantRead(opensocial.DataRequest, 'SortOrder');
    ___.grantRead(opensocial.Email, 'Field');
    ___.grantRead(opensocial.Enum, 'Smoker');
    ___.grantRead(opensocial.Enum, 'Drinker');
    ___.grantRead(opensocial.Enum, 'Gender');
    ___.grantRead(opensocial.Enum, 'LookingFor');
    ___.grantRead(opensocial.Enum, 'Presence');
    ___.grantRead(opensocial.IdSpec, 'Field');
    ___.grantRead(opensocial.IdSpec, 'GroupId');
    ___.grantRead(opensocial.IdSpec, 'PersonId');
    ___.grantRead(opensocial.MediaItem, 'Field');
    ___.grantRead(opensocial.Message, 'Field');
    ___.grantRead(opensocial.MessageCollection, 'Field');
    ___.grantRead(opensocial.Name, 'Field');
    ___.grantRead(opensocial.NavigationParameters, 'Field');
    ___.grantRead(opensocial.Organization, 'Field');
    ___.grantRead(opensocial.Person, 'Field');
    ___.grantRead(opensocial.Phone, 'Field');
    ___.grantRead(opensocial.ResponseItem, 'Error');
    ___.grantRead(opensocial.Url, 'Field');
    ___.grantRead(JsonRpcRequestItem, 'rpc');
    ___.grantRead(JsonRpcRequestItem, 'processData');
    ___.grantRead(JsonRpcRequestItem, 'processResponse');
    ___.grantRead(JsonRpcRequestItem, 'errors');
    ___.grantInnocentMethod(JsonPerson.prototype, 'getDisplayName');
    ___.grantInnocentMethod(JsonPerson.prototype, 'getAppData');
    caja___.whitelistCtors([
        [window, 'JsonRpcRequestItem', Object],
        [opensocial, 'Activity', Object],
        [opensocial, 'Address', Object],
        [opensocial, 'Album', Object],
        [opensocial, 'BodyType', Object],
        [opensocial, 'Container', Object],
        [opensocial, 'Collection', Object],
        [opensocial, 'DataRequest', Object],
        [opensocial, 'DataResponse', Object],
        [opensocial, 'Email', Object],
        [opensocial, 'Enum', Object],
        [opensocial, 'Environment', Object],
        [opensocial, 'IdSpec', Object],
        [opensocial, 'MediaItem', Object],
        [opensocial, 'Message', Object],
        [opensocial, 'Name', Object],
        [opensocial, 'NavigationParameters', Object],
        [opensocial, 'Organization', Object],
        [opensocial, 'Person', Object],
        [opensocial, 'Phone', Object],
        [opensocial, 'ResponseItem', Object],
        [opensocial, 'Url', Object]
    ]);
    caja___.whitelistMeths([
        [opensocial.Activity, 'getField'],
        [opensocial.Activity, 'getId'],
        [opensocial.Activity, 'setField'],
        [opensocial.Address, 'getField'],
        [opensocial.Album, 'getField'],
        [opensocial.BodyType, 'getField'],
        [opensocial.Container, 'getEnvironment'],
        [opensocial.Container, 'requestSendMessage'],
        [opensocial.Container, 'requestShareApp'],
        [opensocial.Container, 'requestCreateActivity'],
        [opensocial.Container, 'hasPermission'],
        [opensocial.Container, 'requestPermission'],
        [opensocial.Container, 'requestData'],
        [opensocial.Container, 'newCreateAlbumRequest'],
        [opensocial.Container, 'newCreateMediaItemRequest'],
        [opensocial.Container, 'newDeleteAlbumRequest'],
        [opensocial.Container, 'newFetchPersonRequest'],
        [opensocial.Container, 'newFetchPeopleRequest'],
        [opensocial.Container, 'newFetchPersonAppDataRequest'],
        [opensocial.Container, 'newUpdatePersonAppDataRequest'],
        [opensocial.Container, 'newRemovePersonAppDataRequest'],
        [opensocial.Container, 'newUpdateAlbumRequest'],
        [opensocial.Container, 'newUpdateMediaItemRequest'],
        [opensocial.Container, 'newFetchActivitiesRequest'],
        [opensocial.Container, 'newFetchAlbumsRequest'],
        [opensocial.Container, 'newFetchMessageCollectionsRequest'],
        [opensocial.Container, 'newFetchMessagesRequest'],
        [opensocial.Container, 'newCollection'],
        [opensocial.Container, 'newPerson'],
        [opensocial.Container, 'newActivity'],
        [opensocial.Container, 'newMediaItem'],
        [opensocial.Container, 'newMessage'],
        [opensocial.Container, 'newIdSpec'],
        [opensocial.Container, 'newNavigationParameters'],
        [opensocial.Container, 'newResponseItem'],
        [opensocial.Container, 'newDataResponse'],
        [opensocial.Container, 'newDataRequest'],
        [opensocial.Container, 'newEnvironment'],
        [opensocial.Container, 'invalidateCache'],
        [opensocial.Collection, 'asArray'],
        [opensocial.Collection, 'each'],
        [opensocial.Collection, 'getById'],
        [opensocial.Collection, 'getOffset'],
        [opensocial.Collection, 'getTotalSize'],
        [opensocial.Collection, 'size'],
        [opensocial.DataRequest, 'add'],
        [opensocial.DataRequest, 'newCreateAlbumRequest'],
        [opensocial.DataRequest, 'newCreateMediaItemRequest'],
        [opensocial.DataRequest, 'newDeleteAlbumRequest'],
        [opensocial.DataRequest, 'newFetchActivitiesRequest'],
        [opensocial.DataRequest, 'newFetchAlbumsRequest'],
        [opensocial.DataRequest, 'newFetchPeopleRequest'],
        [opensocial.DataRequest, 'newFetchPersonAppDataRequest'],
        [opensocial.DataRequest, 'newUpdateAlbumRequest'],
        [opensocial.DataRequest, 'newUpdateMediaItemRequest'],
        [opensocial.DataRequest, 'newFetchPersonRequest'],
        [opensocial.DataRequest, 'newRemovePersonAppDataRequest'],
        [opensocial.DataRequest, 'newUpdatePersonAppDataRequest'],
        [opensocial.DataRequest, 'send'],
        [opensocial.DataResponse, 'get'],
        [opensocial.DataResponse, 'getErrorMessage'],
        [opensocial.DataResponse, 'hadError'],
        [opensocial.Email, 'getField'],
        [opensocial.Enum, 'getDisplayValue'],
        [opensocial.Enum, 'getKey'],
        [opensocial.Environment, 'getDomain'],
        [opensocial.Environment, 'supportsField'],
        [opensocial.IdSpec, 'getField'],
        [opensocial.IdSpec, 'setField'],
        [opensocial.MediaItem, 'getField'],
        [opensocial.MediaItem, 'setField'],
        [opensocial.Message, 'getField'],
        [opensocial.Message, 'setField'],
        [opensocial.Name, 'getField'],
        [opensocial.NavigationParameters, 'getField'],
        [opensocial.NavigationParameters, 'setField'],
        [opensocial.Organization, 'getField'],
        [opensocial.Person, 'getDisplayName'],
        [opensocial.Person, 'getField'],
        [opensocial.Person, 'getId'],
        [opensocial.Person, 'isOwner'],
        [opensocial.Person, 'isViewer'],
        [opensocial.Phone, 'getField'],
        [opensocial.ResponseItem, 'getData'],
        [opensocial.ResponseItem, 'getErrorCode'],
        [opensocial.ResponseItem, 'getErrorMessage'],
        [opensocial.ResponseItem, 'getOriginalDataRequest'],
        [opensocial.ResponseItem, 'hadError'],
        [opensocial.Url, 'getField']
    ]);
    caja___.whitelistFuncs([
        [opensocial.Container, 'setContainer'],
        [opensocial.Container, 'get'],
        [opensocial.Container, 'getField'],
        [opensocial, 'getEnvironment'],
        [opensocial, 'hasPermission'],
        [opensocial, 'newActivity'],
        [opensocial, 'newDataRequest'],
        [opensocial, 'newIdSpec'],
        [opensocial, 'newMediaItem'],
        [opensocial, 'newMessage'],
        [opensocial, 'newNavigationParameters'],
        [opensocial, 'requestCreateActivity'],
        [opensocial, 'requestPermission'],
        [opensocial, 'requestSendMessage'],
        [opensocial, 'requestShareApp']
    ]);
});
gadgets.rpctx = gadgets.rpctx || {};
if (!gadgets.rpctx.wpm) {
    gadgets.rpctx.wpm = function () {
        var process, ready;
        var postMessage;
        var pmSync = false;
        var pmEventDomain = false;
        var isForceSecure = false;

        function testPostMessage() {
            var hit = false;

            function receiveMsg(event) {
                if (event.data == "postmessage.test") {
                    hit = true;
                    if (typeof event.origin === "undefined") {
                        pmEventDomain = true;
                    }
                }
            }
            gadgets.util.attachBrowserEvent(window, "message", receiveMsg, false);
            window.postMessage("postmessage.test", "*");
            if (hit) {
                pmSync = true;
            }
            gadgets.util.removeBrowserEvent(window, "message", receiveMsg, false);
        }

        function onmessage(packet) {
            var rpc = gadgets.json.parse(packet.data);
            if (isForceSecure) {
                if (!rpc || !rpc.f) {
                    return;
                }
                var origRelay = gadgets.rpc.getRelayUrl(rpc.f) || gadgets.util.getUrlParameters()["parent"];
                var origin = gadgets.rpc.getOrigin(origRelay);
                if (!pmEventDomain ? packet.origin !== origin : packet.domain !== /^.+:\/\/([^:]+).*/.exec(origin)[1]) {
                    return;
                }
            }
            process(rpc);
        }
        return {
            getCode: function () {
                return 'wpm';
            },
            isParentVerifiable: function () {
                return true;
            },
            init: function (processFn, readyFn) {
                process = processFn;
                ready = readyFn;
                testPostMessage();
                if (!pmSync) {
                    postMessage = function (win, msg, origin) {
                        win.postMessage(msg, origin);
                    };
                } else {
                    postMessage = function (win, msg, origin) {
                        window.setTimeout(function () {
                            win.postMessage(msg, origin);
                        }, 0);
                    };
                }
                gadgets.util.attachBrowserEvent(window, 'message', onmessage, false);
                ready('..', true);
                return true;
            },
            setup: function (receiverId, token, forceSecure) {
                isForceSecure = forceSecure;
                if (receiverId === '..') {
                    if (isForceSecure) {
                        gadgets.rpc._createRelayIframe(token);
                    } else {
                        gadgets.rpc.call(receiverId, gadgets.rpc.ACK);
                    }
                }
                return true;
            },
            call: function (targetId, from, rpc) {
                var targetWin = gadgets.rpc._getTargetWin(targetId);
                var origRelay = gadgets.rpc.getRelayUrl(targetId) || gadgets.util.getUrlParameters()["parent"];
                var origin = gadgets.rpc.getOrigin(origRelay);
                if (origin) {
                    postMessage(targetWin, gadgets.json.stringify(rpc), origin);
                } else {
                    gadgets.error("No relay set (used as window.postMessage targetOrigin)" + ", cannot send cross-domain message");
                }
                return true;
            },
            relayOnload: function (receiverId, data) {
                ready(receiverId, true);
            }
        };
    }();
}
gadgets.rpctx = gadgets.rpctx || {};
if (!gadgets.rpctx.frameElement) {
    gadgets.rpctx.frameElement = function () {
        var FE_G2C_CHANNEL = '__g2c_rpc';
        var FE_C2G_CHANNEL = '__c2g_rpc';
        var process;
        var ready;

        function callFrameElement(targetId, from, rpc) {
            try {
                if (from !== '..') {
                    var fe = window.frameElement;
                    if (typeof fe[FE_G2C_CHANNEL] === 'function') {
                        if (typeof fe[FE_G2C_CHANNEL][FE_C2G_CHANNEL] !== 'function') {
                            fe[FE_G2C_CHANNEL][FE_C2G_CHANNEL] = function (args) {
                                process(gadgets.json.parse(args));
                            };
                        }
                        fe[FE_G2C_CHANNEL](gadgets.json.stringify(rpc));
                        return true;
                    }
                } else {
                    var frame = document.getElementById(targetId);
                    if (typeof frame[FE_G2C_CHANNEL] === 'function' && typeof frame[FE_G2C_CHANNEL][FE_C2G_CHANNEL] === 'function') {
                        frame[FE_G2C_CHANNEL][FE_C2G_CHANNEL](gadgets.json.stringify(rpc));
                        return true;
                    }
                }
            } catch (e) {}
            return false;
        }
        return {
            getCode: function () {
                return 'fe';
            },
            isParentVerifiable: function () {
                return false;
            },
            init: function (processFn, readyFn) {
                process = processFn;
                ready = readyFn;
                return true;
            },
            setup: function (receiverId, token) {
                if (receiverId !== '..') {
                    try {
                        var frame = document.getElementById(receiverId);
                        frame[FE_G2C_CHANNEL] = function (args) {
                            process(gadgets.json.parse(args));
                        };
                    } catch (e) {
                        return false;
                    }
                }
                if (receiverId === '..') {
                    ready('..', true);
                    var ackFn = function () {
                        window.setTimeout(function () {
                            gadgets.rpc.call(receiverId, gadgets.rpc.ACK);
                        }, 500);
                    };
                    gadgets.util.registerOnLoadHandler(ackFn);
                }
                return true;
            },
            call: function (targetId, from, rpc) {
                return callFrameElement(targetId, from, rpc);
            }
        };
    }();
}
gadgets.rpctx = gadgets.rpctx || {};
if (!gadgets.rpctx.nix) {
    gadgets.rpctx.nix = function () {
        var NIX_WRAPPER = 'GRPC____NIXVBS_wrapper';
        var NIX_GET_WRAPPER = 'GRPC____NIXVBS_get_wrapper';
        var NIX_HANDLE_MESSAGE = 'GRPC____NIXVBS_handle_message';
        var NIX_CREATE_CHANNEL = 'GRPC____NIXVBS_create_channel';
        var MAX_NIX_SEARCHES = 10;
        var NIX_SEARCH_PERIOD = 500;
        var nix_channels = {};
        var isForceSecure = {};
        var ready;
        var numHandlerSearches = 0;

        function conductHandlerSearch() {
            var handler = nix_channels['..'];
            if (handler) {
                return;
            }
            if (++numHandlerSearches > MAX_NIX_SEARCHES) {
                gadgets.warn('Nix transport setup failed, falling back...');
                ready('..', false);
                return;
            }
            if (!handler && window.opener && "GetAuthToken" in window.opener) {
                handler = window.opener;
                if (handler.GetAuthToken() == gadgets.rpc.getAuthToken('..')) {
                    var token = gadgets.rpc.getAuthToken('..');
                    handler.CreateChannel(window[NIX_GET_WRAPPER]('..', token), token);
                    nix_channels['..'] = handler;
                    window.opener = null;
                    ready('..', true);
                    return;
                }
            }
            window.setTimeout(function () {
                conductHandlerSearch();
            }, NIX_SEARCH_PERIOD);
        }

        function getLocationNoHash() {
            var loc = window.location.href;
            var idx = loc.indexOf('#');
            if (idx == -1) {
                return loc;
            }
            return loc.substring(0, idx);
        }

        function setupSecureRelayToParent(rpctoken) {
            var childToken = (0x7FFFFFFF * Math.random()) | 0;
            var data = [getLocationNoHash(), childToken];
            gadgets.rpc._createRelayIframe(rpctoken, data);
            var hash = window.location.href.split('#')[1] || '';

            function relayTimer() {
                var newHash = window.location.href.split('#')[1] || '';
                if (newHash !== hash) {
                    clearInterval(relayTimerId);
                    var params = gadgets.util.getUrlParameters(window.location.href);
                    if (params.childtoken == childToken) {
                        conductHandlerSearch();
                        return;
                    }
                    ready('..', false);
                }
            }
            var relayTimerId = setInterval(relayTimer, 100);
        }
        return {
            getCode: function () {
                return 'nix';
            },
            isParentVerifiable: function (opt_receiverId) {
                if (opt_receiverId) {
                    return isForceSecure[opt_receiverId];
                }
                return false;
            },
            init: function (processFn, readyFn) {
                ready = readyFn;
                if (typeof window[NIX_GET_WRAPPER] !== 'unknown') {
                    window[NIX_HANDLE_MESSAGE] = function (data) {
                        window.setTimeout(function () {
                            processFn(gadgets.json.parse(data));
                        }, 0);
                    };
                    window[NIX_CREATE_CHANNEL] = function (name, channel, token) {
                        if (gadgets.rpc.getAuthToken(name) === token) {
                            nix_channels[name] = channel;
                            ready(name, true);
                        }
                    };
                    var vbscript = 'Class ' + NIX_WRAPPER + '\n ' + 'Private m_Intended\n' + 'Private m_Auth\n' + 'Public Sub SetIntendedName(name)\n ' + 'If isEmpty(m_Intended) Then\n' + 'm_Intended = name\n' + 'End If\n' + 'End Sub\n' + 'Public Sub SetAuth(auth)\n ' + 'If isEmpty(m_Auth) Then\n' + 'm_Auth = auth\n' + 'End If\n' + 'End Sub\n' + 'Public Sub SendMessage(data)\n ' + NIX_HANDLE_MESSAGE + '(data)\n' + 'End Sub\n' + 'Public Function GetAuthToken()\n ' + 'GetAuthToken = m_Auth\n' + 'End Function\n' + 'Public Sub CreateChannel(channel, auth)\n ' + 'Call ' + NIX_CREATE_CHANNEL + '(m_Intended, channel, auth)\n' + 'End Sub\n' + 'End Class\n' + 'Function ' + NIX_GET_WRAPPER + '(name, auth)\n' + 'Dim wrap\n' + 'Set wrap = New ' + NIX_WRAPPER + '\n' + 'wrap.SetIntendedName name\n' + 'wrap.SetAuth auth\n' + 'Set ' + NIX_GET_WRAPPER + ' = wrap\n' + 'End Function';
                    try {
                        window.execScript(vbscript, 'vbscript');
                    } catch (e) {
                        return false;
                    }
                }
                return true;
            },
            setup: function (receiverId, token, forcesecure) {
                isForceSecure[receiverId] = !! forcesecure;
                if (receiverId === '..') {
                    if (forcesecure) {
                        setupSecureRelayToParent(token);
                    } else {
                        conductHandlerSearch();
                    }
                    return true;
                }
                try {
                    var frame = document.getElementById(receiverId);
                    var wrapper = window[NIX_GET_WRAPPER](receiverId, token);
                    frame.contentWindow.opener = wrapper;
                } catch (e) {
                    return false;
                }
                return true;
            },
            call: function (targetId, from, rpc) {
                try {
                    if (nix_channels[targetId]) {
                        nix_channels[targetId].SendMessage(gadgets.json.stringify(rpc));
                    }
                } catch (e) {
                    return false;
                }
                return true;
            },
            relayOnload: function (receiverId, data) {
                var src = data[0] + '#childtoken=' + data[1];
                var childIframe = document.getElementById(receiverId);
                childIframe.src = src;
            }
        };
    }();
}
gadgets.rpctx = gadgets.rpctx || {};
if (!gadgets.rpctx.rmr) {
    gadgets.rpctx.rmr = function () {
        var RMR_SEARCH_TIMEOUT = 500;
        var RMR_MAX_POLLS = 10;
        var rmr_channels = {};
        var process;
        var ready;

        function appendRmrFrame(channelFrame, relayUri, data, opt_frameId) {
            var appendFn = function () {
                document.body.appendChild(channelFrame);
                channelFrame.src = 'about:blank';
                if (opt_frameId) {
                    channelFrame.onload = function () {
                        processRmrData(opt_frameId);
                    };
                }
                channelFrame.src = relayUri + '#' + data;
            };
            if (document.body) {
                appendFn();
            } else {
                gadgets.util.registerOnLoadHandler(function () {
                    appendFn();
                });
            }
        }

        function setupRmr(frameId) {
            if (typeof rmr_channels[frameId] === "object") {
                return;
            }
            var channelFrame = document.createElement('iframe');
            var frameStyle = channelFrame.style;
            frameStyle.position = 'absolute';
            frameStyle.top = '0px';
            frameStyle.border = '0';
            frameStyle.opacity = '0';
            frameStyle.width = '10px';
            frameStyle.height = '1px';
            channelFrame.id = 'rmrtransport-' + frameId;
            channelFrame.name = channelFrame.id;
            var relayUri = gadgets.rpc.getRelayUrl(frameId);
            if (!relayUri) {
                relayUri = gadgets.rpc.getOrigin(gadgets.util.getUrlParameters()["parent"]) + '/robots.txt';
            }
            rmr_channels[frameId] = {
                frame: channelFrame,
                receiveWindow: null,
                relayUri: relayUri,
                searchCounter: 0,
                width: 10,
                waiting: true,
                queue: [],
                sendId: 0,
                recvId: 0
            };
            if (frameId !== '..') {
                appendRmrFrame(channelFrame, relayUri, getRmrData(frameId));
            }
            conductRmrSearch(frameId);
        }

        function conductRmrSearch(frameId) {
            var channelWindow = null;
            rmr_channels[frameId].searchCounter++;
            try {
                var targetWin = gadgets.rpc._getTargetWin(frameId);
                if (frameId === '..') {
                    channelWindow = targetWin.frames['rmrtransport-' + gadgets.rpc.RPC_ID];
                } else {
                    channelWindow = targetWin.frames['rmrtransport-..'];
                }
            } catch (e) {}
            var status = false;
            if (channelWindow) {
                status = registerRmrChannel(frameId, channelWindow);
            }
            if (!status) {
                if (rmr_channels[frameId].searchCounter > RMR_MAX_POLLS) {
                    return;
                }
                window.setTimeout(function () {
                    conductRmrSearch(frameId);
                }, RMR_SEARCH_TIMEOUT);
            }
        }

        function callRmr(targetId, serviceName, from, rpc) {
            var handler = null;
            if (from !== '..') {
                handler = rmr_channels['..'];
            } else {
                handler = rmr_channels[targetId];
            }
            if (handler) {
                if (serviceName !== gadgets.rpc.ACK) {
                    handler.queue.push(rpc);
                }
                if (handler.waiting || (handler.queue.length === 0 && !(serviceName === gadgets.rpc.ACK && rpc && rpc.ackAlone === true))) {
                    return true;
                }
                if (handler.queue.length > 0) {
                    handler.waiting = true;
                }
                var url = handler.relayUri + "#" + getRmrData(targetId);
                try {
                    handler.frame.contentWindow.location = url;
                    var newWidth = handler.width == 10 ? 20 : 10;
                    handler.frame.style.width = newWidth + 'px';
                    handler.width = newWidth;
                } catch (e) {
                    return false;
                }
            }
            return true;
        }

        function getRmrData(toFrameId) {
            var channel = rmr_channels[toFrameId];
            var rmrData = {
                id: channel.sendId
            };
            if (channel) {
                rmrData.d = Array.prototype.slice.call(channel.queue, 0);
                rmrData.d.push({
                    s: gadgets.rpc.ACK,
                    id: channel.recvId
                });
            }
            return gadgets.json.stringify(rmrData);
        }

        function processRmrData(fromFrameId) {
            var channel = rmr_channels[fromFrameId];
            var data = channel.receiveWindow.location.hash.substring(1);
            var rpcObj = gadgets.json.parse(decodeURIComponent(data)) || {};
            var rpcArray = rpcObj.d || [];
            var nonAckReceived = false;
            var noLongerWaiting = false;
            var numBypassed = 0;
            var numToBypass = (channel.recvId - rpcObj.id);
            for (var i = 0; i < rpcArray.length; ++i) {
                var rpc = rpcArray[i];
                if (rpc.s === gadgets.rpc.ACK) {
                    ready(fromFrameId, true);
                    if (channel.waiting) {
                        noLongerWaiting = true;
                    }
                    channel.waiting = false;
                    var newlyAcked = Math.max(0, rpc.id - channel.sendId);
                    channel.queue.splice(0, newlyAcked);
                    channel.sendId = Math.max(channel.sendId, rpc.id || 0);
                    continue;
                }
                nonAckReceived = true;
                if (++numBypassed <= numToBypass) {
                    continue;
                }
                ++channel.recvId;
                process(rpc);
            }
            if (nonAckReceived || (noLongerWaiting && channel.queue.length > 0)) {
                var from = (fromFrameId === '..') ? gadgets.rpc.RPC_ID : '..';
                callRmr(fromFrameId, gadgets.rpc.ACK, from, {
                    ackAlone: nonAckReceived
                });
            }
        }

        function registerRmrChannel(frameId, channelWindow) {
            var channel = rmr_channels[frameId];
            try {
                var canAccess = false;
                canAccess = 'document' in channelWindow;
                if (!canAccess) {
                    return false;
                }
                canAccess = typeof channelWindow['document'] == 'object';
                if (!canAccess) {
                    return false;
                }
                var loc = channelWindow.location.href;
                if (loc === 'about:blank') {
                    return false;
                }
            } catch (ex) {
                return false;
            }
            channel.receiveWindow = channelWindow;

            function onresize() {
                processRmrData(frameId);
            };
            if (typeof channelWindow.attachEvent === "undefined") {
                channelWindow.onresize = onresize;
            } else {
                channelWindow.attachEvent("onresize", onresize);
            }
            if (frameId === '..') {
                appendRmrFrame(channel.frame, channel.relayUri, getRmrData(frameId), frameId);
            } else {
                processRmrData(frameId);
            }
            return true;
        }
        return {
            getCode: function () {
                return 'rmr';
            },
            isParentVerifiable: function () {
                return true;
            },
            init: function (processFn, readyFn) {
                process = processFn;
                ready = readyFn;
                return true;
            },
            setup: function (receiverId, token) {
                try {
                    setupRmr(receiverId);
                } catch (e) {
                    gadgets.warn('Caught exception setting up RMR: ' + e);
                    return false;
                }
                return true;
            },
            call: function (targetId, from, rpc) {
                return callRmr(targetId, rpc.s, from, rpc);
            }
        };
    }();
}
gadgets.rpctx = gadgets.rpctx || {};
if (!gadgets.rpctx.ifpc) {
    gadgets.rpctx.ifpc = function () {
        var iframePool = [];
        var callId = 0;
        var ready;

        function encodeLegacyData(args) {
            var argsEscaped = [];
            for (var i = 0, j = args.length; i < j; ++i) {
                argsEscaped.push(encodeURIComponent(gadgets.json.stringify(args[i])));
            }
            return argsEscaped.join('&');
        }

        function emitInvisibleIframe(src) {
            var iframe;
            for (var i = iframePool.length - 1; i >= 0; --i) {
                var ifr = iframePool[i];
                try {
                    if (ifr && (ifr.recyclable || ifr.readyState === 'complete')) {
                        ifr.parentNode.removeChild(ifr);
                        if (window.ActiveXObject) {
                            iframePool[i] = ifr = null;
                            iframePool.splice(i, 1);
                        } else {
                            ifr.recyclable = false;
                            iframe = ifr;
                            break;
                        }
                    }
                } catch (e) {}
            }
            if (!iframe) {
                iframe = document.createElement('iframe');
                iframe.style.border = iframe.style.width = iframe.style.height = '0px';
                iframe.style.visibility = 'hidden';
                iframe.style.position = 'absolute';
                iframe.onload = function () {
                    this.recyclable = true;
                };
                iframePool.push(iframe);
            }
            iframe.src = src;
            window.setTimeout(function () {
                document.body.appendChild(iframe);
            }, 0);
        }
        return {
            getCode: function () {
                return 'ifpc';
            },
            isParentVerifiable: function () {
                return true;
            },
            init: function (processFn, readyFn) {
                ready = readyFn;
                ready('..', true);
                return true;
            },
            setup: function (receiverId, token) {
                ready(receiverId, true);
                return true;
            },
            call: function (targetId, from, rpc) {
                var relay = gadgets.rpc.getRelayUrl(targetId);
                ++callId;
                if (!relay) {
                    gadgets.warn('No relay file assigned for IFPC');
                    return false;
                }
                var src = null;
                if (rpc.l) {
                    var callArgs = rpc.a;
                    src = [relay, '#', encodeLegacyData([from, callId, 1, 0, encodeLegacyData([from, rpc.s, '', '', from].concat(callArgs))])].join('');
                } else {
                    src = [relay, '#', targetId, '&', from, '@', callId, '&1&0&', encodeURIComponent(gadgets.json.stringify(rpc))].join('');
                }
                emitInvisibleIframe(src);
                return true;
            }
        };
    }();
}
if (!gadgets.rpc) {
    gadgets.rpc = function () {
        var CALLBACK_NAME = '__cb';
        var DEFAULT_NAME = '';
        var ACK = '__ack';
        var SETUP_FRAME_TIMEOUT = 500;
        var SETUP_FRAME_MAX_TRIES = 10;
        var services = {};
        var relayUrl = {};
        var useLegacyProtocol = {};
        var authToken = {};
        var callId = 0;
        var callbacks = {};
        var setup = {};
        var sameDomain = {};
        var params = {};
        var receiverTx = {};
        var earlyRpcQueue = {};
        var isChild = (window.top !== window.self);
        var rpcId = window.name;
        var securityCallback = function () {};
        var LOAD_TIMEOUT = 0;
        var FRAME_PHISH = 1;
        var FORGED_MSG = 2;
        var fallbackTransport = (function () {
            function logFn(name) {
                return function () {
                    gadgets.log("gadgets.rpc." + name + "(" +
                        gadgets.json.stringify(Array.prototype.slice.call(arguments)) + "): call ignored. [caller: " + document.location + ", isChild: " + isChild + "]");
                };
            }
            return {
                getCode: function () {
                    return "noop";
                },
                isParentVerifiable: function () {
                    return true;
                },
                init: logFn("init"),
                setup: logFn("setup"),
                call: logFn("call")
            };
        })();
        if (gadgets.util) {
            params = gadgets.util.getUrlParameters();
        }

        function getTransport() {
            return typeof window.postMessage === 'function' ? gadgets.rpctx.wpm : typeof window.postMessage === 'object' ? gadgets.rpctx.wpm : window.ActiveXObject ? gadgets.rpctx.nix : navigator.userAgent.indexOf('WebKit') > 0 ? gadgets.rpctx.rmr : navigator.product === 'Gecko' ? gadgets.rpctx.frameElement : gadgets.rpctx.ifpc;
        }

        function transportReady(receiverId, readySuccess) {
            var tx = transport;
            if (!readySuccess) {
                tx = fallbackTransport;
            }
            receiverTx[receiverId] = tx;
            var earlyQueue = earlyRpcQueue[receiverId] || [];
            for (var i = 0; i < earlyQueue.length; ++i) {
                var rpc = earlyQueue[i];
                rpc.t = getAuthToken(receiverId);
                tx.call(receiverId, rpc.f, rpc);
            }
            earlyRpcQueue[receiverId] = [];
        }
        var mainPageUnloading = false,
            hookedUnload = false;

        function hookMainPageUnload() {
            if (hookedUnload) {
                return;
            }

            function onunload() {
                mainPageUnloading = true;
            }
            gadgets.util.attachBrowserEvent(window, 'unload', onunload, false);
            hookedUnload = true;
        }

        function relayOnload(targetId, sourceId, token, data, relayWindow) {
            if (!authToken[sourceId] || authToken[sourceId] !== token) {
                gadgets.error("Invalid auth token. " + authToken[sourceId] + " vs " + token);
                securityCallback(sourceId, FORGED_MSG);
            }
            relayWindow.onunload = function () {
                if (setup[sourceId] && !mainPageUnloading) {
                    securityCallback(sourceId, FRAME_PHISH);
                    gadgets.rpc.removeReceiver(sourceId);
                }
            };
            hookMainPageUnload();
            data = gadgets.json.parse(decodeURIComponent(data));
            transport.relayOnload(sourceId, data);
        }

        function process(rpc) {
            if (rpc && typeof rpc.s === 'string' && typeof rpc.f === 'string' && rpc.a instanceof Array) {
                if (authToken[rpc.f]) {
                    if (authToken[rpc.f] !== rpc.t) {
                        gadgets.error("Invalid auth token. " + authToken[rpc.f] + " vs " + rpc.t);
                        securityCallback(rpc.f, FORGED_MSG);
                    }
                }
                if (rpc.s === ACK) {
                    window.setTimeout(function () {
                        transportReady(rpc.f, true);
                    }, 0);
                    return;
                }
                if (rpc.c) {
                    rpc.callback = function (result) {
                        gadgets.rpc.call(rpc.f, CALLBACK_NAME, null, rpc.c, result);
                    };
                }
                var result = (services[rpc.s] || services[DEFAULT_NAME]).apply(rpc, rpc.a);
                if (rpc.c && typeof result !== 'undefined') {
                    gadgets.rpc.call(rpc.f, CALLBACK_NAME, null, rpc.c, result);
                }
            }
        }

        function getOrigin(url) {
            if (!url) {
                return "";
            }
            url = url.toLowerCase();
            if (url.indexOf("//") == 0) {
                url = window.location.protocol + url;
            }
            if (url.indexOf("://") == -1) {
                url = window.location.protocol + "//" + url;
            }
            var host = url.substring(url.indexOf("://") + 3);
            var slashPos = host.indexOf("/");
            if (slashPos != -1) {
                host = host.substring(0, slashPos);
            }
            var protocol = url.substring(0, url.indexOf("://"));
            var portStr = "";
            var portPos = host.indexOf(":");
            if (portPos != -1) {
                var port = host.substring(portPos + 1);
                host = host.substring(0, portPos);
                if ((protocol === "http" && port !== "80") || (protocol === "https" && port !== "443")) {
                    portStr = ":" + port;
                }
            }
            return protocol + "://" + host + portStr;
        }

        function getTargetWin(id) {
            if (typeof id === "undefined" || id === "..") {
                return window.parent;
            }
            id = String(id);
            var target = window.frames[id];
            if (target) {
                return target;
            }
            target = document.getElementById(id);
            if (target && target.contentWindow) {
                return target.contentWindow;
            }
            return null;
        }
        var transport = getTransport();
        services[DEFAULT_NAME] = function () {
            gadgets.warn('Unknown RPC service: ' + this.s);
        };
        services[CALLBACK_NAME] = function (callbackId, result) {
            var callback = callbacks[callbackId];
            if (callback) {
                delete callbacks[callbackId];
                callback(result);
            }
        };

        function setupFrame(frameId, token, forcesecure) {
            if (setup[frameId] === true) {
                return;
            }
            if (typeof setup[frameId] === 'undefined') {
                setup[frameId] = 0;
            }
            var tgtFrame = document.getElementById(frameId);
            if (frameId === '..' || tgtFrame != null) {
                if (transport.setup(frameId, token, forcesecure) === true) {
                    setup[frameId] = true;
                    return;
                }
            }
            if (setup[frameId] !== true && setup[frameId]++ < SETUP_FRAME_MAX_TRIES) {
                window.setTimeout(function () {
                    setupFrame(frameId, token, forcesecure)
                }, SETUP_FRAME_TIMEOUT);
            } else {
                receiverTx[frameId] = fallbackTransport;
                setup[frameId] = true;
            }
        }

        function callSameDomain(target, rpc) {
            if (typeof sameDomain[target] === 'undefined') {
                sameDomain[target] = false;
                var targetRelay = gadgets.rpc.getRelayUrl(target);
                if (getOrigin(targetRelay) !== getOrigin(window.location.href)) {
                    return false;
                }
                var targetEl = getTargetWin(target);
                try {
                    sameDomain[target] = targetEl.gadgets.rpc.receiveSameDomain;
                } catch (e) {
                    gadgets.error("Same domain call failed: parent= incorrectly set.");
                }
            }
            if (typeof sameDomain[target] === 'function') {
                sameDomain[target](rpc);
                return true;
            }
            return false;
        }

        function setRelayUrl(targetId, url, opt_useLegacy) {
            if (!/http(s)?:\/\/.+/.test(url)) {
                if (url.indexOf("//") == 0) {
                    url = window.location.protocol + url;
                } else if (url.charAt(0) == '/') {
                    url = window.location.protocol + "//" + window.location.host + url;
                } else if (url.indexOf("://") == -1) {
                    url = window.location.protocol + "//" + url;
                }
            }
            relayUrl[targetId] = url;
            useLegacyProtocol[targetId] = !! opt_useLegacy;
        }

        function getAuthToken(targetId) {
            return authToken[targetId];
        }

        function setAuthToken(targetId, token, forcesecure) {
            token = token || "";
            authToken[targetId] = String(token);
            setupFrame(targetId, token, forcesecure);
        }

        function setupContainerGadgetContext(rpctoken, opt_forcesecure) {
            function init(config) {
                var configRpc = config ? config.rpc : {};
                var parentRelayUrl = configRpc.parentRelayUrl;
                if (parentRelayUrl.substring(0, 7) !== 'http://' && parentRelayUrl.substring(0, 8) !== 'https://' && parentRelayUrl.substring(0, 2) !== '//') {
                    if (typeof params.parent === "string" && params.parent !== "") {
                        if (parentRelayUrl.substring(0, 1) !== '/') {
                            var lastSlash = params.parent.lastIndexOf('/');
                            parentRelayUrl = params.parent.substring(0, lastSlash + 1) + parentRelayUrl;
                        } else {
                            parentRelayUrl = getOrigin(params.parent) + parentRelayUrl;
                        }
                    }
                }
                var useLegacy = !! configRpc.useLegacyProtocol;
                setRelayUrl('..', parentRelayUrl, useLegacy);
                if (useLegacy) {
                    transport = gadgets.rpctx.ifpc;
                    transport.init(process, transportReady);
                }
                var forceSecure = opt_forcesecure || params.forcesecure || false;
                setAuthToken('..', rpctoken, forceSecure);
            }
            var requiredConfig = {
                parentRelayUrl: gadgets.config.NonEmptyStringValidator
            };
            gadgets.config.register("rpc", requiredConfig, init);
        }

        function setupContainerGenericIframe(rpctoken, opt_parent, opt_forcesecure) {
            var forcesecure = opt_forcesecure || params.forcesecure || false;
            var parent = opt_parent || params.parent;
            if (parent) {
                setRelayUrl('..', parent);
                setAuthToken('..', rpctoken, forcesecure);
            }
        }

        function setupChildIframe(gadgetId, opt_frameurl, opt_authtoken, opt_forcesecure) {
            if (!gadgets.util) {
                return;
            }
            var childIframe = document.getElementById(gadgetId);
            if (!childIframe) {
                throw new Error("Cannot set up gadgets.rpc receiver with ID: " + gadgetId + ", element not found.");
            }
            var relayUrl = opt_frameurl || childIframe.src;
            setRelayUrl(gadgetId, relayUrl);
            var childParams = gadgets.util.getUrlParameters(childIframe.src);
            var rpctoken = opt_authtoken || childParams.rpctoken;
            var forcesecure = opt_forcesecure || childParams.forcesecure;
            setAuthToken(gadgetId, rpctoken, forcesecure);
        }

        function setupReceiver(targetId, opt_receiverurl, opt_authtoken, opt_forcesecure) {
            if (targetId === '..') {
                var rpctoken = opt_authtoken || params.rpctoken || params.ifpctok || "";
                if (window['__isgadget'] === true) {
                    setupContainerGadgetContext(rpctoken, opt_forcesecure);
                } else {
                    setupContainerGenericIframe(rpctoken, opt_receiverurl, opt_forcesecure);
                }
            } else {
                setupChildIframe(targetId, opt_receiverurl, opt_authtoken, opt_forcesecure);
            }
        }
        return {
            config: function (config) {
                if (typeof config.securityCallback === 'function') {
                    securityCallback = config.securityCallback;
                }
            },
            register: function (serviceName, handler) {
                if (serviceName === CALLBACK_NAME || serviceName === ACK) {
                    throw new Error("Cannot overwrite callback/ack service");
                }
                if (serviceName === DEFAULT_NAME) {
                    throw new Error("Cannot overwrite default service:" + " use registerDefault");
                }
                services[serviceName] = handler;
            },
            unregister: function (serviceName) {
                if (serviceName === CALLBACK_NAME || serviceName === ACK) {
                    throw new Error("Cannot delete callback/ack service");
                }
                if (serviceName === DEFAULT_NAME) {
                    throw new Error("Cannot delete default service:" + " use unregisterDefault");
                }
                delete services[serviceName];
            },
            registerDefault: function (handler) {
                services[DEFAULT_NAME] = handler;
            },
            unregisterDefault: function () {
                delete services[DEFAULT_NAME];
            },
            forceParentVerifiable: function () {
                if (!transport.isParentVerifiable()) {
                    transport = gadgets.rpctx.ifpc;
                }
            },
            call: function (targetId, serviceName, callback, var_args) {
                targetId = targetId || '..';
                var from = '..';
                if (targetId === '..') {
                    from = rpcId;
                }
                ++callId;
                if (callback) {
                    callbacks[callId] = callback;
                }
                var rpc = {
                    s: serviceName,
                    f: from,
                    c: callback ? callId : 0,
                    a: Array.prototype.slice.call(arguments, 3),
                    t: authToken[targetId],
                    l: useLegacyProtocol[targetId]
                };
                if (targetId !== '..' && !document.getElementById(targetId)) {
                    gadgets.log("WARNING: attempted send to nonexistent frame: " + targetId);
                    return;
                }
                if (callSameDomain(targetId, rpc)) {
                    return;
                }
                var channel = receiverTx[targetId];
                if (!channel) {
                    if (!earlyRpcQueue[targetId]) {
                        earlyRpcQueue[targetId] = [rpc];
                    } else {
                        earlyRpcQueue[targetId].push(rpc);
                    }
                    return;
                }
                if (useLegacyProtocol[targetId]) {
                    channel = gadgets.rpctx.ifpc;
                }
                if (channel.call(targetId, from, rpc) === false) {
                    receiverTx[targetId] = fallbackTransport;
                    transport.call(targetId, from, rpc);
                }
            },
            getRelayUrl: function (targetId) {
                var url = relayUrl[targetId];
                if (url && url.substring(0, 1) === '/') {
                    if (url.substring(1, 2) === '/') {
                        url = document.location.protocol + url;
                    } else {
                        url = document.location.protocol + '//' + document.location.host + url;
                    }
                }
                return url;
            },
            setRelayUrl: setRelayUrl,
            setAuthToken: setAuthToken,
            setupReceiver: setupReceiver,
            getAuthToken: getAuthToken,
            removeReceiver: function (receiverId) {
                delete relayUrl[receiverId];
                delete useLegacyProtocol[receiverId];
                delete authToken[receiverId];
                delete setup[receiverId];
                delete sameDomain[receiverId];
                delete receiverTx[receiverId];
            },
            getRelayChannel: function () {
                return transport.getCode();
            },
            receive: function (fragment, otherWindow) {
                if (fragment.length > 4) {
                    process(gadgets.json.parse(decodeURIComponent(fragment[fragment.length - 1])));
                } else {
                    relayOnload.apply(null, fragment.concat(otherWindow));
                }
            },
            receiveSameDomain: function (rpc) {
                rpc.a = Array.prototype.slice.call(rpc.a);
                window.setTimeout(function () {
                    process(rpc);
                }, 0);
            },
            getOrigin: getOrigin,
            getReceiverOrigin: function (receiverId) {
                var channel = receiverTx[receiverId];
                if (!channel) {
                    return null;
                }
                if (!channel.isParentVerifiable(receiverId)) {
                    return null;
                }
                var origRelay = gadgets.rpc.getRelayUrl(receiverId) || gadgets.util.getUrlParameters().parent;
                return gadgets.rpc.getOrigin(origRelay);
            },
            init: function () {
                if (transport.init(process, transportReady) === false) {
                    transport = fallbackTransport;
                }
                if (isChild) {
                    setupReceiver('..');
                }
            },
            _getTargetWin: getTargetWin,
            _createRelayIframe: function (token, data) {
                var relay = gadgets.rpc.getRelayUrl('..');
                if (!relay) {
                    return null;
                }
                var src = relay + '#..&' + rpcId + '&' + token + '&' +
                    encodeURIComponent(gadgets.json.stringify(data));
                var iframe = document.createElement('iframe');
                iframe.style.border = iframe.style.width = iframe.style.height = '0px';
                iframe.style.visibility = 'hidden';
                iframe.style.position = 'absolute';

                function appendFn() {
                    document.body.appendChild(iframe);
                    iframe.src = 'javascript:"<html></html>"';
                    iframe.src = src;
                }
                if (document.body) {
                    appendFn();
                } else {
                    gadgets.util.registerOnLoadHandler(function () {
                        appendFn();
                    });
                }
                return iframe;
            },
            ACK: ACK,
            RPC_ID: rpcId,
            SEC_ERROR_LOAD_TIMEOUT: LOAD_TIMEOUT,
            SEC_ERROR_FRAME_PHISH: FRAME_PHISH,
            SEC_ERROR_FORGED_MSG: FORGED_MSG
        };
    }();
    gadgets.rpc.init();
}
var dmm = dmm || {};
dmm.Util = {};
dmm.Util.OverlayType = {
    SHARE_APP: "requestShareAppCallback",
    PAYMENT: "requestPaymentCallback"
};
dmm.Util.wrapMethod = function (obj, method, func) {
    if (typeof obj[method] !== "function") {
        gadgets.warn("wrapped object should be function!");
        return;
    }
    if (typeof func !== "function") {
        gadgets.warn("wrapper object should be function!");
        return;
    }
    var f = obj[method];
    obj[method] = function () {
        var ret = f.apply(obj, Array.prototype.slice.call(arguments));
        func();
        return ret;
    }
};
dmm.Util.wrapMethods = function (obj, methods, func) {
    if (methods.constructor !== Array) {
        gadgets.warn("funcnames should be an Array!");
        return;
    }
    for (var i = 0, j = methods.length; i < j; i++) {
        this.wrapMethod(obj, methods[i], func);
    }
};
dmm.Util.registerOpenOverlayHandler = function (callback) {
    var func = callback || function () {};
    this.wrapMethods(opensocial, ["requestShareApp", "requestPayment"], func);
};
dmm.Util.registerCloseOverlayHandler = function (callback) {
    var func = callback || function () {};
    gadgets.rpc.call(null, "dmm.setCloseOverlayCallback", null, true);
    gadgets.rpc.register("dmm.closeOverlayCallback", function (type) {
        func(type);
    });
};
dmm.Person = function (params) {
    this.fields_ = params || {};
};
dmm.Person.Field = {
    BLOOD_TYPE: "bloodType",
    USER_TYPE: "userType",
    GRADE: "grade"
};
dmm.BillingItem = dmm.BillingItem || {};
dmm.BillingItem.Field = {
    IMAGE_URL: "imageUrl",
    NAME: "name"
};
dmm.Payment = dmm.Payment || {};
dmm.Payment.Field = {
    PAYMENT_ID: "payment_id"
};
dmm.IgnoreList = function (params) {
    this.fields_ = params || {};
};
dmm.IgnoreList.Field = {
    ID: "id",
    TARGET_ID: "target_id"
};
dmm.IgnoreListRequestFields = {
    COUNT: "count",
    FIRST: "startIndex",
    PERSON_ID: "personId"
};
dmm.IgnoreList.prototype.getField = function (key, opt_params) {
    return opensocial.Container.getField(this.fields_, key, opt_params);
};
dmm.IgnoreList.prototype.setField = function (key, data) {
    return this.fields_[key] = data;
};
dmm.IgnoreList.prototype.getId = function () {
    return this.getField(dmm.IgnoreList.Field.ID);
};
dmm.IgnoreList.prototype.getTargetId = function () {
    return this.getField(dmm.IgnoreList.Field.TARGET_ID);
};
dmm.newFetchIgnoreListRequest = function (idSpec, opt_params) {
    var rpc = {
        method: "ignorelist.get"
    };
    rpc.params = opensocial.Container.get().translateIdSpec(idSpec);
    rpc.params.appId = "@app";
    FieldTranslations.translateNetworkDistance(idSpec, rpc.params);
    for (field in opt_params) {
        rpc.params[field] = opt_params[field];
    }
    return new JsonRpcRequestItem(rpc, function (rawJson) {
        var rawJson = rawJson['list'];
        var ignorelist = [];
        if (rawJson) {
            for (var i = 0; i < rawJson.length; i++) {
                ignorelist.push(new dmm.IgnoreList({
                    "id": rawJson[i]["id"],
                    "target_id": rawJson[i]["ignorelistId"]
                }));
            }
        }
        return new opensocial.Collection(ignorelist);
    });
};
dmm.requestFetchIgnoreList = function (idSpec, opt_params, callback) {
    callback = callback || function () {};
    var req = opensocial.newDataRequest();
    req.add(dmm.newFetchIgnoreListRequest(idSpec, opt_params), "key");
    req.send(function (response) {
        callback(response.get("key"));
    });
};
dmm.UserText = function (params) {
    this.fields_ = params || {};
};
dmm.UserText.Field = {
    TEXT_ID: "textId",
    APP_ID: "appId",
    DATA: "data",
    AUTHOR_ID: "authorId",
    OWNER_ID: "ownerId",
    STATUS: "status",
    CTIME: "ctime",
    MTIME: "mtime"
};
dmm.UserText.prototype.getField = function (key, opt_params) {
    return opensocial.Container.getField(this.fields_, key, opt_params);
};
dmm.UserText.prototype.setField = function (key, data) {
    return this.fields_[key] = data;
};
dmm.UserText.prototype.getTextId = function () {
    return this.getField(dmm.UserText.Field.TEXT_ID);
};
dmm.UserText.prototype.getAppId = function () {
    return this.getField(dmm.UserText.Field.APP_ID);
};
dmm.UserText.prototype.getData = function () {
    return this.getField(dmm.UserText.Field.DATA);
};
dmm.UserText.prototype.getAuthorId = function () {
    return this.getField(dmm.UserText.Field.AUTHOR_ID);
};
dmm.UserText.prototype.getOwnerId = function () {
    return this.getField(dmm.UserText.Field.OWNER_ID);
};
dmm.UserText.prototype.getStatus = function () {
    return this.getField(dmm.UserText.Field.STATUS);
};
dmm.UserText.prototype.getCtime = function () {
    return this.getField(dmm.UserText.Field.CTIME);
};
dmm.UserText.prototype.getMtime = function () {
    return this.getField(dmm.UserText.Field.MTIME);
};
dmm.newFetchInspectionRequest = function (opt_params) {
    var rpc = {
        method: "inspection.get"
    };
    rpc.params = {
        "appId": "@app"
    };
    if (opt_params["textId"] && !(opt_params["textId"] instanceof Array)) {
        opt_params["textId"] = [opt_params["textId"]];
    }
    for (field in opt_params) {
        rpc.params[field] = opt_params[field];
    }
    return new JsonRpcRequestItem(rpc, function (rawJson) {
        var usertext = [];
        if (rawJson) {
            for (var i = 0; i < rawJson.length; i++) {
                usertext.push(new dmm.UserText(rawJson[i]));
            }
        }
        return new opensocial.Collection(usertext);
    });
};
dmm.requestFetchInspection = function (opt_params, callback) {
    callback = callback || function () {};
    var req = opensocial.newDataRequest();
    req.add(dmm.newFetchInspectionRequest(opt_params), "key");
    req.send(function (response) {
        callback(response.get("key"));
    });
};
dmm.newCreateInspectionRequest = function (opt_params) {
    var rpc = {
        method: "inspection.create"
    };
    var idSpec = opensocial.newIdSpec({
        'userId': 'VIEWER'
    });
    rpc.params = opensocial.Container.get().translateIdSpec(idSpec);
    rpc.params.appId = "@app";
    FieldTranslations.translateNetworkDistance(idSpec, rpc.params);
    rpc.params.params = {
        "data": opt_params["data"]
    };
    return new JsonRpcRequestItem(rpc, function (rawJson) {
        var usertext = [];
        if (rawJson) {
            for (var i = 0; i < rawJson.length; i++) {
                usertext.push(new dmm.UserText(rawJson[i]));
            }
        }
        return new opensocial.Collection(usertext);
    });
};
dmm.requestCreateInspection = function (opt_params, callback) {
    callback = callback || function () {};
    var req = opensocial.newDataRequest();
    req.add(dmm.newCreateInspectionRequest(opt_params), "key");
    req.send(function (response) {
        callback(response.get("key"));
    });
};
dmm.newUpdateInspectionRequest = function (opt_params) {
    var rpc = {
        method: "inspection.update"
    };
    var idSpec = opensocial.newIdSpec({
        'userId': 'VIEWER'
    });
    rpc.params = opensocial.Container.get().translateIdSpec(idSpec);
    rpc.params.appId = "@app";
    FieldTranslations.translateNetworkDistance(idSpec, rpc.params);
    rpc.params.textId = opt_params["textId"];
    rpc.params.params = {
        "data": opt_params["data"]
    };
    return new JsonRpcRequestItem(rpc, function (rawJson) {
        var usertext = [];
        if (rawJson) {
            for (var i = 0; i < rawJson.length; i++) {
                usertext.push(new dmm.UserText(rawJson[i]));
            }
        }
        return new opensocial.Collection(usertext);
    });
};
dmm.requestUpdateInspection = function (opt_params, callback) {
    callback = callback || function () {};
    var req = opensocial.newDataRequest();
    req.add(dmm.newUpdateInspectionRequest(opt_params), "key");
    req.send(function (response) {
        callback(response.get("key"));
    });
};
dmm.newRemoveInspectionRequest = function (opt_params) {
    var rpc = {
        method: "inspection.delete"
    };
    var idSpec = opensocial.newIdSpec({
        'userId': 'VIEWER'
    });
    rpc.params = opensocial.Container.get().translateIdSpec(idSpec);
    rpc.params.appId = "@app";
    FieldTranslations.translateNetworkDistance(idSpec, rpc.params);
    if (opt_params["textId"] && !(opt_params["textId"] instanceof Array)) {
        opt_params["textId"] = [opt_params["textId"]];
    }
    rpc.params.textId = opt_params["textId"];
    return new JsonRpcRequestItem(rpc, function (rawJson) {
        var usertext = [];
        if (rawJson) {
            for (var i = 0; i < rawJson.length; i++) {
                usertext.push(new dmm.UserText(rawJson[i]));
            }
        }
        return new opensocial.Collection(usertext);
    });
};
dmm.requestRemoveInspection = function (opt_params, callback) {
    callback = callback || function () {};
    var req = opensocial.newDataRequest();
    req.add(dmm.newRemoveInspectionRequest(opt_params), "key");
    req.send(function (response) {
        callback(response.get("key"));
    });
};
dmm.Thumbnail = function (params) {
    this.fields_ = params || {};
};
dmm.Thumbnail.Field = {
    ID: "id",
    URL: "url"
};
dmm.ThumbnailRequestFields = {
    PERSON_ID: "personId",
    SIZE: "size"
};
dmm.Thumbnail.Size = {
    NORMAL: "normal",
    SMALL: "small",
    LARGE: "large",
    HUGE: "huge"
};
dmm.Thumbnail.prototype.getField = function (key, opt_params) {
    return opensocial.Container.getField(this.fields_, key, opt_params);
};
dmm.Thumbnail.prototype.setField = function (key, data) {
    return this.fields_[key] = data;
};
dmm.Thumbnail.prototype.getId = function () {
    return this.getField(dmm.Thumbnail.Field.ID);
};
dmm.Thumbnail.prototype.getUrl = function () {
    return this.getField(dmm.Thumbnail.Field.URL);
};
dmm.newFetchThumbnailRequest = function (opt_params) {
    var rpc = {
        method: "thumbnail.get"
    };
    rpc.params = {
        "appId": "@app"
    };
    if (opt_params["personId"] && !(opt_params["personId"] instanceof Array)) {
        opt_params["personId"] = [opt_params["personId"]];
    }
    for (field in opt_params) {
        rpc.params[field] = opt_params[field];
    }
    return new JsonRpcRequestItem(rpc, function (rawJson) {
        var thumbnail = [];
        if (rawJson) {
            for (var i = 0; i < rawJson.length; i++) {
                thumbnail.push(new dmm.Thumbnail(rawJson[i]));
            }
        }
        return new opensocial.Collection(thumbnail);
    });
};
dmm.requestFetchThumbnail = function (opt_params, callback) {
    callback = callback || function () {};
    var req = opensocial.newDataRequest();
    req.add(dmm.newFetchThumbnailRequest(opt_params), "key");
    req.send(function (response) {
        callback(response.get("key"));
    });
};
dmm.Activity = function (params) {
    this.fields_ = params || {};
};
dmm.Activity.Field = {
    MOBILE_URL: "mobileUrl",
    TOUCH_URL: "touchUrl"
};
dmm.Url = function (params) {
    this.fields_ = params || {};
};
dmm.Url.Field = {
    VALUE: "value"
};
dmm.Message = function (params) {
    this.fields_ = params || {};
};
dmm.Message.UrlType = {
    MOBILE: "mobile",
    TOUCH: "touch",
    CANVAS: "canvas"
};
gadgets.rpc.register('update_security_token', function (token) {
    shindig.auth.updateSecurityToken(token);
});
gadgets.window = gadgets.window || {};
(function () {
    var oldHeight;

    function parseIntFromElemPxAttribute(elem, attr) {
        var style = window.getComputedStyle(elem, "");
        var value = style.getPropertyValue(attr);
        value.match(/^([0-9]+)/);
        return parseInt(RegExp.$1, 10);
    }

    function getHeightForWebkit() {
        var result = 0;
        var queue = [document.body];
        while (queue.length > 0) {
            var elem = queue.shift();
            var children = elem.childNodes;
            for (var i = 0; i < children.length; i++) {
                var child = children[i];
                if (typeof child.offsetTop !== 'undefined' && typeof child.scrollHeight !== 'undefined') {
                    var bottom = child.offsetTop + child.scrollHeight +
                        parseIntFromElemPxAttribute(child, "margin-bottom");
                    result = Math.max(result, bottom);
                }
                queue.push(child);
            }
        }
        return result + parseIntFromElemPxAttribute(document.body, "border-bottom") + parseIntFromElemPxAttribute(document.body, "margin-bottom") + parseIntFromElemPxAttribute(document.body, "padding-bottom");
    }
    gadgets.window.adjustHeight = function (opt_height) {
        var newHeight = parseInt(opt_height, 10);
        var heightAutoCalculated = false;
        if (isNaN(newHeight)) {
            heightAutoCalculated = true;
            var vh = gadgets.window.getViewportDimensions().height;
            var body = document.body;
            var docEl = document.documentElement;
            if (document.compatMode === 'CSS1Compat' && docEl.scrollHeight) {
                newHeight = docEl.scrollHeight !== vh ? docEl.scrollHeight : docEl.offsetHeight;
            } else if (navigator.userAgent.indexOf('AppleWebKit') >= 0) {
                newHeight = getHeightForWebkit();
            } else if (body && docEl) {
                var sh = docEl.scrollHeight;
                var oh = docEl.offsetHeight;
                if (docEl.clientHeight !== oh) {
                    sh = body.scrollHeight;
                    oh = body.offsetHeight;
                }
                if (sh > vh) {
                    newHeight = sh > oh ? sh : oh;
                } else {
                    newHeight = sh < oh ? sh : oh;
                }
            }
        }
        if (newHeight !== oldHeight && !isNaN(newHeight) && !(heightAutoCalculated && newHeight === 0)) {
            oldHeight = newHeight;
            gadgets.rpc.call(null, "resize_iframe", null, newHeight);
        }
    };
}());
var _IG_AdjustIFrameHeight = gadgets.window.adjustHeight;
var tamings___ = tamings___ || [];
tamings___.push(function (imports) {
    caja___.whitelistFuncs([
        [gadgets.window, 'adjustHeight'],
        [gadgets.window, 'getViewportDimensions']
    ]);
});
window['FieldTranslations'] = (function () {
    function translateEnumJson(enumJson) {
        if (enumJson) {
            enumJson.key = enumJson.value;
        }
    };

    function translateUrlJson(urlJson) {
        if (urlJson) {
            urlJson.address = urlJson.value;
        }
    };
    return {
        'translateEnumJson': translateEnumJson,
        'translateUrlJson': translateUrlJson,
        'translateServerPersonToJsPerson': function (serverJson, opt_params) {
            if (serverJson.emails) {
                for (var i = 0; i < serverJson.emails.length; i++) {
                    serverJson.emails[i].address = serverJson.emails[i].value;
                }
            }
            if (serverJson.phoneNumbers) {
                for (var p = 0; p < serverJson.phoneNumbers.length; p++) {
                    serverJson.phoneNumbers[p].number = serverJson.phoneNumbers[p].value;
                }
            }
            if (serverJson.birthday) {
                serverJson.dateOfBirth = serverJson.birthday;
            }
            if (serverJson.utcOffset) {
                serverJson.timeZone = serverJson.utcOffset;
            }
            if (serverJson.addresses) {
                for (var j = 0; j < serverJson.addresses.length; j++) {
                    serverJson.addresses[j].unstructuredAddress = serverJson.addresses[j].formatted;
                }
            }
            if (serverJson.gender) {
                var key = serverJson.gender == 'male' ? 'MALE' : (serverJson.gender == 'female') ? 'FEMALE' : null;
                serverJson.gender = {
                    key: key,
                    displayValue: serverJson.gender
                };
            }
            translateUrlJson(serverJson.profileSong);
            translateUrlJson(serverJson.profileVideo);
            if (serverJson.urls) {
                for (var u = 0; u < serverJson.urls.length; u++) {
                    translateUrlJson(serverJson.urls[u]);
                }
            }
            translateEnumJson(serverJson.drinker);
            translateEnumJson(serverJson.lookingFor);
            translateEnumJson(serverJson.networkPresence);
            translateEnumJson(serverJson.smoker);
            if (serverJson.organizations) {
                serverJson.jobs = [];
                serverJson.schools = [];
                for (var o = 0; o < serverJson.organizations.length; o++) {
                    var org = serverJson.organizations[o];
                    if (org.type == 'job') {
                        serverJson.jobs.push(org);
                    } else if (org.type == 'school') {
                        serverJson.schools.push(org);
                    }
                }
            }
            if (serverJson.name) {
                serverJson.name.unstructured = serverJson.name.formatted;
            }
            if (serverJson.appData) {
                serverJson.appData = opensocial.Container.escape(serverJson.appData, opt_params, true);
            }
        },
        'translateJsPersonFieldsToServerFields': function (fields) {
            for (var i = 0; i < fields.length; i++) {
                if (fields[i] == 'dateOfBirth') {
                    fields[i] = 'birthday';
                } else if (fields[i] == 'timeZone') {
                    fields[i] = 'utcOffset';
                } else if (fields[i] == 'jobs') {
                    fields[i] = 'organizations';
                } else if (fields[i] == 'schools') {
                    fields[i] = 'organizations';
                }
            }
            fields.push('id');
            fields.push('displayName');
        },
        'translateIsoStringToDate': function (isoString) {
            var regexp = '([0-9]{4})(-([0-9]{2})(-([0-9]{2})' + '(T([0-9]{2}):([0-9]{2})(:([0-9]{2})(\.([0-9]+))?)?' + '(Z|(([-+])([0-9]{2}):([0-9]{2})))?)?)?)?';
            var d = isoString.match(new RegExp(regexp));
            var offset = 0;
            var date = new Date(d[1], 0, 1);
            if (d[3]) {
                date.setMonth(d[3] - 1);
            }
            if (d[5]) {
                date.setDate(d[5]);
            }
            if (d[7]) {
                date.setHours(d[7]);
            }
            if (d[8]) {
                date.setMinutes(d[8]);
            }
            if (d[10]) {
                date.setSeconds(d[10]);
            }
            if (d[12]) {
                date.setMilliseconds(Number("0." + d[12]) * 1000);
            }
            if (d[14]) {
                offset = (Number(d[16]) * 60) + Number(d[17]);
                offset *= ((d[15] == '-') ? 1 : -1);
            }
            offset -= date.getTimezoneOffset();
            var time = (Number(date) + (offset * 60 * 1000));
            return new Date(Number(time));
        },
        'addAppDataAsProfileFields': function (opt_params) {
            if (opt_params) {
                if (opt_params['appData']) {
                    var appDataKeys = opt_params['appData'];
                    if (typeof appDataKeys === 'string') {
                        appDataKeys = [appDataKeys];
                    }
                    var profileDetail = opt_params['profileDetail'] || [];
                    for (var i = 0; i < appDataKeys.length; i++) {
                        if (appDataKeys[i] === '*') {
                            profileDetail.push('appData');
                        } else {
                            profileDetail.push('appData.' + appDataKeys[i]);
                        }
                    }
                    opt_params['appData'] = appDataKeys;
                }
            }
        },
        'translateStandardArguments': function (opt_params, rpc_params) {
            if (opt_params['first']) {
                rpc_params.startIndex = opt_params['first'];
            }
            if (opt_params['max']) {
                rpc_params.count = opt_params['max'];
            }
            if (opt_params['sortOrder']) {
                rpc_params.sortBy = opt_params['sortOrder'];
            }
            if (opt_params['filter']) {
                rpc_params.filterBy = opt_params['filter'];
            }
            if (opt_params['filterOp']) {
                rpc_params.filterOp = opt_params['filterOp'];
            }
            if (opt_params['filterValue']) {
                rpc_params.filterValue = opt_params['filterValue'];
            }
            if (opt_params['fields']) {
                rpc_params.fields = opt_params['fields'];
            }
        },
        'translateNetworkDistance': function (idSpec, rpc_params) {
            if (idSpec.getField('networkDistance')) {
                rpc_params.networkDistance = idSpec.getField('networkDistance');
            }
        }
    };
})();
var JsonActivity = function (opt_params, opt_skipConversions) {
    opt_params = opt_params || {};
    if (!opt_skipConversions) {
        JsonActivity.constructArrayObject(opt_params, "mediaItems", JsonMediaItem);
    }
    opensocial.Activity.call(this, opt_params);
};
JsonActivity.inherits(opensocial.Activity);
JsonActivity.prototype.toJsonObject = function () {
    var jsonObject = JsonActivity.copyFields(this.fields_);
    var oldMediaItems = jsonObject['mediaItems'] || [];
    var newMediaItems = [];
    for (var i = 0; i < oldMediaItems.length; i++) {
        newMediaItems[i] = oldMediaItems[i].toJsonObject();
    }
    jsonObject['mediaItems'] = newMediaItems;
    return jsonObject;
};
var JsonMediaItem = function (opt_params) {
    opensocial.MediaItem.call(this, opt_params['mimeType'], opt_params['url'], opt_params);
};
JsonMediaItem.inherits(opensocial.MediaItem);
JsonMediaItem.prototype.toJsonObject = function () {
    return JsonActivity.copyFields(this.fields_);
};
JsonActivity.constructArrayObject = function (map, fieldName, className) {
    var fieldValue = map[fieldName];
    if (fieldValue) {
        for (var i = 0; i < fieldValue.length; i++) {
            fieldValue[i] = new className(fieldValue[i]);
        }
    }
};
JsonActivity.copyFields = function (oldObject) {
    var newObject = {};
    for (var field in oldObject) {
        newObject[field] = oldObject[field];
    }
    return newObject;
};
var JsonPerson = function (opt_params) {
    opt_params = opt_params || {};
    JsonPerson.constructObject(opt_params, "bodyType", opensocial.BodyType);
    JsonPerson.constructObject(opt_params, "currentLocation", opensocial.Address);
    JsonPerson.constructObject(opt_params, "name", opensocial.Name);
    JsonPerson.constructObject(opt_params, "profileSong", opensocial.Url);
    JsonPerson.constructObject(opt_params, "profileVideo", opensocial.Url);
    JsonPerson.constructDate(opt_params, "dateOfBirth");
    JsonPerson.constructArrayObject(opt_params, "addresses", opensocial.Address);
    JsonPerson.constructArrayObject(opt_params, "emails", opensocial.Email);
    JsonPerson.constructArrayObject(opt_params, "jobs", opensocial.Organization);
    JsonPerson.constructArrayObject(opt_params, "phoneNumbers", opensocial.Phone);
    JsonPerson.constructArrayObject(opt_params, "schools", opensocial.Organization);
    JsonPerson.constructArrayObject(opt_params, "urls", opensocial.Url);
    JsonPerson.constructEnum(opt_params, "gender");
    JsonPerson.constructEnum(opt_params, "smoker");
    JsonPerson.constructEnum(opt_params, "drinker");
    JsonPerson.constructEnum(opt_params, "networkPresence");
    JsonPerson.constructEnumArray(opt_params, "lookingFor");
    opensocial.Person.call(this, opt_params, opt_params['isOwner'], opt_params['isViewer']);
};
JsonPerson.inherits(opensocial.Person);
JsonPerson.constructEnum = function (map, fieldName) {
    var fieldValue = map[fieldName];
    if (fieldValue) {
        map[fieldName] = new opensocial.Enum(fieldValue.key, fieldValue.displayValue);
    }
};
JsonPerson.constructEnumArray = function (map, fieldName) {
    var fieldValue = map[fieldName];
    if (fieldValue) {
        for (var i = 0; i < fieldValue.length; i++) {
            fieldValue[i] = new opensocial.Enum(fieldValue[i].key, fieldValue[i].displayValue);
        }
    }
};
JsonPerson.constructObject = function (map, fieldName, className) {
    var fieldValue = map[fieldName];
    if (fieldValue) {
        map[fieldName] = new className(fieldValue);
    }
};
JsonPerson.constructDate = function (map, fieldName) {
    var fieldValue = map[fieldName];
    if (fieldValue) {
        map[fieldName] = FieldTranslations.translateIsoStringToDate(fieldValue);
    }
};
JsonPerson.constructArrayObject = function (map, fieldName, className) {
    var fieldValue = map[fieldName];
    if (fieldValue) {
        for (var i = 0; i < fieldValue.length; i++) {
            fieldValue[i] = new className(fieldValue[i]);
        }
    }
};
JsonPerson.prototype.getDisplayName = function () {
    return this.getField("displayName");
};
JsonPerson.prototype.getAppData = function (key) {
    var appData = this.getField("appData");
    return appData && appData[key];
};
var JsonMessageCollection = function (opt_params) {
    opt_params = opt_params || {};
    opensocial.MessageCollection.call(this, opt_params);
};
JsonMessageCollection.inherits(opensocial.MessageCollection);
JsonMessageCollection.prototype.toJsonObject = function () {
    return JsonMessageCollection.copyFields(this.fields_);
};
JsonMessageCollection.copyFields = function (oldObject) {
    var newObject = {};
    for (var field in oldObject) {
        newObject[field] = oldObject[field];
    }
    return newObject;
};
var JsonMessage = function (body, opt_params) {
    opt_params = opt_params || {};
    opensocial.Message.call(this, body, opt_params);
};
JsonMessage.inherits(opensocial.Message);
JsonMessage.prototype.toJsonObject = function () {
    return JsonMessage.copyFields(this.fields_);
};
JsonMessage.copyFields = function (oldObject) {
    var newObject = {};
    for (var field in oldObject) {
        newObject[field] = oldObject[field];
    }
    return newObject;
};
opensocial.BillingItem = function (params) {
    this.fields_ = params || {};
    this.fields_[opensocial.BillingItem.Field.COUNT] = this.fields_[opensocial.BillingItem.Field.COUNT] || 1;
};
opensocial.BillingItem.Field = {
    SKU_ID: 'skuId',
    PRICE: 'price',
    COUNT: 'count',
    DESCRIPTION: 'description'
};
opensocial.BillingItem.prototype.getField = function (key, opt_params) {
    return opensocial.Container.getField(this.fields_, key, opt_params);
};
opensocial.BillingItem.prototype.setField = function (key, data) {
    return this.fields_[key] = data;
};
opensocial.Payment = function (params) {
    this.fields_ = params || {};
    this.fields_[opensocial.Payment.Field.PAYMENT_TYPE] = this.fields_[opensocial.Payment.Field.PAYMENT_TYPE] || opensocial.Payment.PaymentType.PAYMENT;
};
opensocial.Payment.prototype.isPayment = function () {
    return this.fields_[opensocial.Payment.Field.PAYMENT_TYPE] == opensocial.Payment.PaymentType.PAYMENT;
};
opensocial.Payment.prototype.isCredit = function () {
    return this.fields_[opensocial.Payment.Field.PAYMENT_TYPE] == opensocial.Payment.PaymentType.CREDIT;
};
opensocial.Payment.prototype.isComplete = function () {
    return !!this.fields_[opensocial.Payment.Field.PAYMENT_COMPLETE];
};
opensocial.Payment.Field = {
    SANDBOX: 'sandbox',
    ITEMS: 'items',
    AMOUNT: 'amount',
    MESSAGE: 'message',
    PARAMETERS: 'parameters',
    PAYMENT_TYPE: 'paymentType',
    ORDER_ID: 'orderId',
    ORDERED_TIME: 'orderedTime',
    SUBMITTED_TIME: 'submittedTime',
    EXECUTED_TIME: 'executedTime',
    RESPONSE_CODE: 'responseCode',
    RESPONSE_MESSAGE: 'responseMessage',
    PAYMENT_COMPLETE: 'paymentComplete'
};
opensocial.Payment.prototype.getField = function (key, opt_params) {
    return opensocial.Container.getField(this.fields_, key, opt_params);
};
opensocial.Payment.prototype.setField = function (key, data) {
    return this.fields_[key] = data;
};
opensocial.Payment.PaymentType = {
    PAYMENT: 'payment',
    CREDIT: 'credit'
};
opensocial.Payment.ResponseCode = {
    APP_LOGIC_ERROR: 'appLogicError',
    APP_NETWORK_FAILURE: 'appNetworkFailure',
    INSUFFICIENT_MONEY: 'insufficientMoney',
    INVALID_TOKEN: 'invalidToken',
    MALFORMED_REQUEST: 'malformedRequest',
    NOT_IMPLEMENTED: 'notImplemented',
    OK: 'ok',
    PAYMENT_ERROR: 'paymentError',
    PAYMENT_PROCESSOR_ALREADY_OPENED: 'paymentProcessorAlreadyOpened',
    UNKNOWN_ERROR: 'unknownError',
    USER_CANCELLED: 'userCancelled'
};
opensocial.Payment.RecordsRequestFields = {
    SANDBOX: 'sandbox',
    MAX: 'max',
    INCOMPLETE_ONLY: 'incompleteOnly'
};
var JsonPayment = function (opt_params, opt_skipConversions) {
    opt_params = opt_params || {};
    if (!opt_skipConversions) {
        JsonPayment.constructArrayObject(opt_params, 'items', JsonBillingItem);
    }
    opensocial.Payment.call(this, opt_params);
};
JsonPayment.inherits(opensocial.Payment);
JsonPayment.prototype.toJsonObject = function () {
    var jsonObject = JsonPayment.copyFields(this.fields_);
    var oldBillingItems = jsonObject['items'] || [];
    var newBillingItems = [];
    for (var i = 0; i < oldBillingItems.length; i++) {
        newBillingItems[i] = oldBillingItems[i].toJsonObject();
    }
    jsonObject['items'] = newBillingItems;
    return jsonObject;
};
var JsonBillingItem = function (opt_params) {
    opensocial.BillingItem.call(this, opt_params);
};
JsonBillingItem.inherits(opensocial.BillingItem);
JsonBillingItem.prototype.toJsonObject = function () {
    return JsonPayment.copyFields(this.fields_);
};
JsonPayment.constructArrayObject = function (map, fieldName, className) {
    var fieldValue = map[fieldName];
    if (fieldValue) {
        for (var i = 0; i < fieldValue.length; i++) {
            fieldValue[i] = new className(fieldValue[i]);
        }
    }
};
JsonPayment.copyFields = function (oldObject) {
    var newObject = {};
    for (var field in oldObject) {
        newObject[field] = oldObject[field];
    }
    return newObject;
};
opensocial.requestPayment = function (payment, opt_callback) {
    opensocial.Container.get().requestPayment(payment, opt_callback);
};
opensocial.requestPaymentRecords = function (opt_callback, opt_params) {
    opensocial.Container.get().requestPaymentRecords(opt_callback, opt_params);
};
opensocial.newPayment = function (params) {
    return opensocial.Container.get().newPayment(params);
};
opensocial.newBillingItem = function (params) {
    return opensocial.Container.get().newBillingItem(params);
};
var JsonRpcContainer = function (configParams) {
    opensocial.Container.call(this);
    var path = configParams.path;
    this.path_ = path.replace("%host%", document.location.host);
    var invalidatePath = configParams.invalidatePath;
    this.invalidatePath_ = invalidatePath.replace("%host%", document.location.host);
    var supportedFieldsArray = configParams.supportedFields;
    var supportedFieldsMap = {};
    for (var objectType in supportedFieldsArray) {
        if (supportedFieldsArray.hasOwnProperty(objectType)) {
            supportedFieldsMap[objectType] = {};
            for (var i = 0; i < supportedFieldsArray[objectType].length; i++) {
                var supportedField = supportedFieldsArray[objectType][i];
                supportedFieldsMap[objectType][supportedField] = true;
            }
        }
    }
    this.environment_ = new opensocial.Environment(configParams.domain, supportedFieldsMap);
    this.securityToken_ = shindig.auth.getSecurityToken();
    gadgets.rpc.register('shindig.requestShareApp_callback', JsonRpcContainer.requestShareAppCallback_);
};
var JsonRpcRequestItem = function (rpc, opt_processData) {
    this.rpc = rpc;
    this.processData = opt_processData || function (rawJson) {
        return rawJson;
    };
    this.processResponse = function (originalDataRequest, rawJson, error, errorMessage) {
        var errorCode = error ? JsonRpcContainer.translateHttpError(error['code']) : null;
        return new opensocial.ResponseItem(originalDataRequest, error ? null : this.processData(rawJson), errorCode, errorMessage);
    };
};
(function () {
    var callbackIdStore = {};
    JsonRpcContainer.inherits(opensocial.Container);
    JsonRpcContainer.prototype.getEnvironment = function () {
        return this.environment_;
    };
    JsonRpcContainer.prototype.requestSendMessage = function (recipients, message, opt_callback, opt_params) {
        opt_callback = opt_callback || function () {};
        var req = opensocial.newDataRequest();
        var viewer = opensocial.newIdSpec({
            'userId': 'VIEWER'
        });
        message.setField(opensocial.Message.Field.RECIPIENTS, [recipients]);
        req.add(this.newCreateMessageRequest(viewer, message), 'key');
        req.send(function (response) {
            opt_callback(response.get('key'));
        });
    };
    JsonRpcContainer.prototype.requestPayment = function (payment, opt_callback) {
        var req = opensocial.newDataRequest();
        var viewer = opensocial.newIdSpec({
            'userId': 'VIEWER'
        });
        if (!payment) {
            if (opt_callback) {
                opt_callback(new opensocial.ResponseItem(null, payment, opensocial.Payment.ResponseCode.MALFORMED_REQUEST, 'Payment object is undefined.'));
            }
            return;
        }
        gadgets.rpc.register("dmm.requestPaymentCallback", function (status, response) {
            var data = null;
            var responseItem = null;
            if (status == 200) {
                if (response) {
                    payment.setField(dmm.Payment.Field.PAYMENT_ID, response.payment_id);
                }
                if (response.response_code == "OK") {
                    payment.setField(opensocial.Payment.Field.RESPONSE_CODE, opensocial.Payment.ResponseCode.OK);
                } else {
                    payment.setField(opensocial.Payment.Field.RESPONSE_CODE, opensocial.Payment.ResponseCode.USER_CANCELLED);
                }
                responseItem = new opensocial.ResponseItem(null, payment);
            } else {
                var errorCode = opensocial.Payment.ResponseCode.PAYMENT_ERROR;
                var errorMessage = (response) ? response.message : 'unknown error';
                responseItem = new opensocial.ResponseItem(null, data, errorCode, errorMessage);
            }
            if (opt_callback) {
                opt_callback(responseItem);
            }
        });
        req.add(this.newCreatePaymentRequest(viewer, payment), 'key');
        req.send(function (response) {
            if (response.hadError()) {
                if (opt_callback) {
                    opt_callback(new opensocial.ResponseItem(null, payment, opensocial.Payment.ResponseCode.PAYMENT_ERROR, 'request payment error'));
                }
                return;
            }
            gadgets.rpc.call(null, "dmm.requestPayment", null, response.get('key').getData());
        });
    };
    JsonRpcContainer.prototype.requestShareApp = function (recipientIds, reason, opt_callback, opt_params) {
        gadgets.rpc.register("dmm.requestShareAppCallback", function (status, recipientIds) {
            var data = null;
            if (recipientIds) {
                data = {
                    'recipientIds': recipientIds
                };
            }
            var responseitem = null;
            if (status == 200) {
                responseitem = new opensocial.ResponseItem(null, data);
            } else {
                var errorCode, errorMessage;
                if (status == 403) {
                    errorCode = opensocial.ResponseItem.Error.FORBIDDEN;
                    errorMessage = 'Viewer does not use this application.';
                } else {
                    errorCode = opensocial.ResponseItem.Error.INTERNAL_ERROR;
                    errorMessage = ['Unknown Error: ', status];
                }
                responseitem = new opensocial.ResponseItem(null, data, errorCode, errorMessage);
            }
            opt_callback(responseitem);
        });
        gadgets.rpc.call(null, "dmm.requestShareApp", null, opt_callback, recipientIds, reason, opt_params);
    };
    JsonRpcContainer.requestShareAppCallback_ = function (callbackId, success, opt_errorCode, recipientIds) {
        callback = callbackIdStore[callbackId];
        if (callback) {
            callbackIdStore[callbackId] = null;
            var data = null;
            if (recipientIds) {
                data = {
                    'recipientIds': recipientIds
                };
            }
            var responseItem = new opensocial.ResponseItem(null, data, opt_errorCode);
            callback(responseItem);
        }
    };
    JsonRpcContainer.prototype.requestCreateActivity = function (activity, priority, opt_callback) {
        opt_callback = opt_callback || function () {};
        var req = opensocial.newDataRequest();
        var viewer = opensocial.newIdSpec({
            'userId': 'VIEWER'
        });
        req.add(this.newCreateActivityRequest(viewer, activity), 'key');
        req.send(function (response) {
            opt_callback(response.get('key'));
        });
    };
    JsonRpcContainer.prototype.requestData = function (dataRequest, callback) {
        callback = callback || function () {};
        var requestObjects = dataRequest.getRequestObjects();
        var totalRequests = requestObjects.length;
        if (totalRequests === 0) {
            window.setTimeout(function () {
                callback(new opensocial.DataResponse({}, true));
            }, 0);
            return;
        }
        var jsonBatchData = new Array(totalRequests);
        for (var j = 0; j < totalRequests; j++) {
            var requestObject = requestObjects[j];
            jsonBatchData[j] = requestObject.request.rpc;
            if (requestObject.key) {
                jsonBatchData[j].id = requestObject.key;
            }
        }
        var sendResponse = function (result) {
            if (result.errors[0]) {
                JsonRpcContainer.generateErrorResponse(result, requestObjects, callback);
                return;
            }
            result = result.result || result.data;
            var globalError = false;
            var responseMap = {};
            for (var i = 0; i < result.length; i++) {
                result[result[i].id] = result[i];
            }
            for (var k = 0; k < requestObjects.length; k++) {
                var request = requestObjects[k];
                var response = result[k];
                if (request.key && response.id !== request.key) {
                    throw "Request key(" + request.key + ") and response id(" + response.id + ") do not match";
                }
                var rawData = response.result || response.data;
                var error = response.error;
                var errorMessage = "";
                if (error) {
                    errorMessage = error.message;
                }
                var processedData = request.request.processResponse(request.request, rawData, error, errorMessage);
                globalError = globalError || processedData.hadError();
                if (request.key) {
                    responseMap[request.key] = processedData;
                }
            }
            var dataResponse = new opensocial.DataResponse(responseMap, globalError);
            callback(dataResponse);
        };
        var makeRequestParams = {
            "CONTENT_TYPE": "JSON",
            "METHOD": "POST",
            "AUTHORIZATION": "SIGNED",
            "POST_DATA": gadgets.json.stringify(jsonBatchData)
        };
        var url = [this.path_];
        var token = shindig.auth.getSecurityToken();
        if (token) {
            url.push("?st=", encodeURIComponent(token));
        }
        this.sendRequest(url.join(''), sendResponse, makeRequestParams, "application/json");
    };
    JsonRpcContainer.prototype.sendRequest = function (relativeUrl, callback, params, contentType) {
        gadgets.io.makeNonProxiedRequest(relativeUrl, callback, params, contentType);
    };
    JsonRpcContainer.generateErrorResponse = function (result, requestObjects, callback) {
        var globalErrorCode = JsonRpcContainer.translateHttpError(result.rc || result.result.error || result.data.error) || opensocial.ResponseItem.Error.INTERNAL_ERROR;
        var errorResponseMap = {};
        for (var i = 0; i < requestObjects.length; i++) {
            errorResponseMap[requestObjects[i].key] = new opensocial.ResponseItem(requestObjects[i].request, null, globalErrorCode);
        }
        callback(new opensocial.DataResponse(errorResponseMap, true));
    };
    JsonRpcContainer.translateHttpError = function (httpError) {
        if (httpError == 501) {
            return opensocial.ResponseItem.Error.NOT_IMPLEMENTED;
        } else if (httpError == 401) {
            return opensocial.ResponseItem.Error.UNAUTHORIZED;
        } else if (httpError == 403) {
            return opensocial.ResponseItem.Error.FORBIDDEN;
        } else if (httpError == 400) {
            return opensocial.ResponseItem.Error.BAD_REQUEST;
        } else if (httpError == 500) {
            return opensocial.ResponseItem.Error.INTERNAL_ERROR;
        } else if (httpError == 404) {
            return opensocial.ResponseItem.Error.BAD_REQUEST;
        } else if (httpError == 417) {
            return opensocial.ResponseItem.Error.LIMIT_EXCEEDED;
        }
    };
    JsonRpcContainer.prototype.makeIdSpec = function (id) {
        return opensocial.newIdSpec({
            'userId': id
        });
    };
    JsonRpcContainer.prototype.translateIdSpec = function (newIdSpec) {
        var userIds = newIdSpec.getField('userId');
        var groupId = newIdSpec.getField('groupId');
        if (!opensocial.Container.isArray(userIds)) {
            userIds = [userIds];
        }
        for (var i = 0; i < userIds.length; i++) {
            if (userIds[i] === 'OWNER') {
                userIds[i] = '@owner';
            } else if (userIds[i] === 'VIEWER') {
                userIds[i] = '@viewer';
            }
        }
        if (groupId === 'FRIENDS') {
            groupId = "@friends";
        } else if (groupId == 'ALL') {
            groupId = "@all";
        } else if (groupId === 'SELF' || !groupId) {
            groupId = "@self";
        }
        return {
            userId: userIds,
            groupId: groupId
        };
    };
    JsonRpcContainer.prototype.newFetchPersonRequest = function (id, opt_params) {
        var peopleRequest = this.newFetchPeopleRequest(this.makeIdSpec(id), opt_params);
        var me = this;
        return new JsonRpcRequestItem(peopleRequest.rpc, function (rawJson) {
            return me.createPersonFromJson(rawJson, opt_params);
        });
    };
    JsonRpcContainer.prototype.newFetchPeopleRequest = function (idSpec, opt_params) {
        var rpc = {
            method: "people.get"
        };
        rpc.params = this.translateIdSpec(idSpec);
        FieldTranslations.addAppDataAsProfileFields(opt_params);
        FieldTranslations.translateStandardArguments(opt_params, rpc.params);
        FieldTranslations.translateNetworkDistance(idSpec, rpc.params);
        if (opt_params['profileDetail']) {
            FieldTranslations.translateJsPersonFieldsToServerFields(opt_params['profileDetail']);
            rpc.params.fields = opt_params['profileDetail'];
        }
        var me = this;
        return new JsonRpcRequestItem(rpc, function (rawJson) {
            var jsonPeople;
            if (rawJson['list']) {
                jsonPeople = rawJson['list'];
            } else {
                jsonPeople = [rawJson];
            }
            var people = [];
            for (var i = 0; i < jsonPeople.length; i++) {
                people.push(me.createPersonFromJson(jsonPeople[i], opt_params));
            }
            return new opensocial.Collection(people, rawJson['startIndex'], rawJson['totalResults']);
        });
    };
    JsonRpcContainer.prototype.createPersonFromJson = function (serverJson, opt_params) {
        FieldTranslations.translateServerPersonToJsPerson(serverJson, opt_params);
        return new JsonPerson(serverJson);
    };
    JsonRpcContainer.prototype.getFieldsList = function (keys) {
        if (this.hasNoKeys(keys) || this.isWildcardKey(keys[0])) {
            return [];
        } else {
            return keys;
        }
    };
    JsonRpcContainer.prototype.hasNoKeys = function (keys) {
        return !keys || keys.length === 0;
    };
    JsonRpcContainer.prototype.isWildcardKey = function (key) {
        return key === "*";
    };
    JsonRpcContainer.prototype.newActivity = function (opt_params) {
        return new JsonActivity(opt_params, true);
    };
    JsonRpcContainer.prototype.newCreateActivityRequest = function (idSpec, activity) {
        var rpc = {
            method: "activities.create"
        };
        rpc.params = this.translateIdSpec(idSpec);
        rpc.params.appId = "@app";
        FieldTranslations.translateNetworkDistance(idSpec, rpc.params);
        rpc.params.activity = activity.toJsonObject();
        return new JsonRpcRequestItem(rpc);
    };
    JsonRpcContainer.prototype.newCreateMessageRequest = function (idSpec, message) {
        var rpc = {
            method: "messages.create"
        };
        rpc.params = this.translateIdSpec(idSpec);
        rpc.params.appId = "@app";
        FieldTranslations.translateNetworkDistance(idSpec, rpc.params);
        rpc.params.message = message.toJsonObject();
        return new JsonRpcRequestItem(rpc);
    };
    JsonRpcContainer.prototype.newCreatePaymentRequest = function (idSpec, payment) {
        var rpc = {
            method: "paymentjs.create"
        };
        rpc.params = this.translateIdSpec(idSpec);
        rpc.params.appId = "@app";
        FieldTranslations.translateNetworkDistance(idSpec, rpc.params);
        rpc.params.params = payment.toJsonObject();
        return new JsonRpcRequestItem(rpc);
    };
})();
JsonRpcContainer.prototype.newMessage = function (body, opt_params) {
    return new JsonMessage(body, opt_params);
};
JsonRpcContainer.prototype.newMessageCollection = function (opt_params) {
    return new JsonMessageCollection(opt_params);
};
JsonRpcContainer.prototype.newBillingItem = function (opt_params) {
    return new JsonBillingItem(opt_params);
};
JsonRpcContainer.prototype.newPayment = function (opt_params) {
    return new JsonPayment(opt_params, true);
};
var requiredConfig = {
    "path": gadgets.config.NonEmptyStringValidator,
    "invalidatePath": gadgets.config.NonEmptyStringValidator,
    "domain": gadgets.config.NonEmptyStringValidator,
    "enableCaja": gadgets.config.BooleanValidator,
    "supportedFields": gadgets.config.ExistsValidator
};
gadgets.config.register("opensocial", requiredConfig, function (config) {
    ShindigContainer = function () {
        JsonRpcContainer.call(this, config["opensocial"]);
    };
    ShindigContainer.inherits(JsonRpcContainer);
    opensocial.Container.setContainer(new ShindigContainer());
});
opensocial.DataRequest.prototype.newUpdatePersonAppDataRequest_09 = opensocial.DataRequest.prototype.newUpdatePersonAppDataRequest;
opensocial.DataRequest.prototype.newUpdatePersonAppDataRequest = function (id, key, value) {
    if (id !== opensocial.IdSpec.PersonId.VIEWER) {
        throw Error("Cannot update app data for person " + id);
    }
    return this.newUpdatePersonAppDataRequest_09(key, value);
};
opensocial.DataRequest.prototype.newRemovePersonAppDataRequest_09 = opensocial.DataRequest.prototype.newRemovePersonAppDataRequest;
opensocial.DataRequest.prototype.newRemovePersonAppDataRequest = function (id, keys) {
    if (id !== opensocial.IdSpec.PersonId.VIEWER) {
        throw Error("Cannot remove app data for person " + id);
    }
    return this.newRemovePersonAppDataRequest_09(keys);
};
gadgets.config.init({
    "core.io": {
        "proxyUrl": "\/\/%host%\/gadgets\/proxy?container=default&refresh=%refresh%&url=%url%%rewriteMime%",
        "jsonProxyUrl": "\/\/%host%\/gadgets\/makeRequest"
    },
    "rpc": {
        "parentRelayUrl": "\/container\/rpc_relay.html",
        "useLegacyProtocol": false
    },
    "opensocial": {
        "path": "http:\/\/%host%\/social\/rpc",
        "invalidatePath": "http:\/\/%host%\/gadgets\/api\/rpc",
        "domain": "osapi.dmm.com",
        "enableCaja": false,
        "supportedFields": {
            "person": ["id", {
                "name": ["familyName", "givenName", "unstructured"]
            }, "thumbnailUrl", "profileUrl", "id", {
                "name": ["familyName", "givenName", "unstructured"]
            }, "thumbnailUrl", "profileUrl"],
            "activity": ["appId", "body", "bodyId", "externalId", "id", "mediaItems", "postedTime", "priority", "streamFaviconUrl", "streamSourceUrl", "streamTitle", "streamUrl", "templateParams", "title", "url", "userId", "appId", "body", "bodyId", "externalId", "id", "mediaItems", "postedTime", "priority", "streamFaviconUrl", "streamSourceUrl", "streamTitle", "streamUrl", "templateParams", "title", "url", "userId"],
            "album": ["id", "thumbnailUrl", "title", "description", "location", "ownerId", "id", "thumbnailUrl", "title", "description", "location", "ownerId"],
            "mediaItem": ["album_id", "created", "description", "duration", "file_size", "id", "language", "last_updated", "location", "mime_type", "num_comments", "num_views", "num_votes", "rating", "start_time", "tagged_people", "tags", "thumbnail_url", "title", "type", "url", "album_id", "created", "description", "duration", "file_size", "id", "language", "last_updated", "location", "mime_type", "num_comments", "num_views", "num_votes", "rating", "start_time", "tagged_people", "tags", "thumbnail_url", "title", "type", "url"]
        }
    },
    "core.util": {
        "": {},
        "core.none": {},
        "globals": {},
        "core.config": {},
        "core.json": {},
        "core.util": {},
        "core.prefs": {},
        "shindig.auth": {},
        "core.io": {},
        "core.legacy": {},
        "dynamic-height.util": {},
        "flash": {},
        "locked-domain": {},
        "opensocial-reference": {},
        "rpc": {},
        "dmm": {},
        "auth-refresh": {},
        "dynamic-height": {},
        "opensocial-base": {},
        "opensocial-payment": {},
        "security-token": {},
        "opensocial-jsonrpc": {},
        "opensocial": {},
        "opensocial-0.9": {},
        "opensocial-0.8": {}
    },
    "osapi.services": {
        "gadgets.rpc": ["container.listMethods"],
        "http:\/\/%host%\/rpc": ["messages.update", "albums.update", "activities.delete", "activities.update", "activities.supportedFields", "albums.get", "activities.get", "mediaitems.update", "messages.get", "appdata.get", "system.listMethods", "people.supportedFields", "messages.create", "mediaitems.delete", "mediaitems.create", "people.get", "people.create", "albums.delete", "messages.delete", "appdata.update", "activities.create", "mediaitems.get", "albums.create", "appdata.delete", "people.update", "appdata.create"],
        "http:\/\/%host%\/gadgets\/api\/rpc": ["cache.invalidate", "http.head", "http.get", "http.put", "http.post", "http.delete"]
    }
});
gadgets.Prefs.setMessages_([]);
gadgets.Prefs.setDefaultPrefs_([]);
gadgets.io.preloaded_ = {};
