static const char canvas_htm[] PROGMEM = "<!-- Author : Mudassar Tamboli -->\n"\
"\n"\
"<!DOCTYPE html>\n"\
"<html>\n"\
"<title> ESP32-OV7670 - Websocket Demo By Mudassar Tamboli </title>\n"\
"<script type = \"text/javascript\">\n"\
"    var ws = null;\n"\
"    var r = 0;\n"\
"    var capturecount = 1;\n"\
"    var ln = 0;\n"\
"    var flag = 0;\n"\
"    var xres = 0;\n"\
"    var yres = 0;\n"\
"    var canvas;\n"\
"    var ctx;\n"\
"    var imgData;\n"\
"    var gcanvasid = \"canvas-QQ-VGA\";    \n"\
"    var camera_ip = \"192.168.4.1\";\n"\
"\n"\
"    function initWebSocket() {\n"\
"    \n"\
"        if (\"WebSocket\" in window) {\n"\
"            if (ws != null) {\n"\
"                ws.close();\n"\
"            } \n"\
"          \n"\
"            ws = new WebSocket('ws://' +  camera_ip + ':81/', ['arduino']);\n"\
"            if (ws == null) {\n"\
"                document.getElementById(\"connecting\").innerText = \"Failed to connect to camera [ \" + camera_ip + \" ]\";\n"\
"                return;    \n"\
"            }\n"\
"            ws.binaryType = 'arraybuffer';\n"\
"\n"\
"\n"\
"            // open websocket \n"\
"            ws.onopen = function() {\n"\
"                document.getElementById(\"canvas7670\").style.visibility = \"visible\";\n"\
"                document.getElementById(\"connecting\").style.visibility = \"hidden\";\n"\
"                document.getElementById(\"constatus\").innerText = \"Connected to \" + ws.url;\n"\
"                if (gcanvasid != null && gcanvasid != \"\") {\n"\
"                    capture(gcanvasid);\n"\
"                }\n"\
"            };//ws.onopen\n"\
"           \n"\
"            // receive message \n"\
"            ws.onmessage = function (evt) { \n"\
"                var arraybuffer = evt.data;\n"\
"                if (arraybuffer.byteLength == 1) {\n"\
"                    flag  = new Uint8Array(evt.data); // Start Flag\n"\
"                    if (flag == 0xAA) {\n"\
"                        ln = 0;                   \n"\
"                    }\n"\
"                    if (flag == 0xFF) {\n"\
"                       //alert(\"Last Block\");\n"\
"                    }\n"\
"\n"\
"                    if (flag == 0x11) {\n"\
"                        //alert(\"Camera IP\");\n"\
"                    }\n"\
"\n"\
"                } else {\n"\
"\n"\
"                    if (flag == 0x11) {\n"\
"                        //alert(\"Camera IP \" + evt.data);\n"\
"                        camera_ip = evt.data;\n"\
"                        document.getElementById(\"wifi-ip\").innerText = camera_ip;\n"\
"                        flag = 0;         \n"\
"                    } else {\n"\
"                        var bytearray = new Uint8Array(evt.data);\n"\
"                        display(bytearray, arraybuffer.byteLength, flag);\n"\
"                    }\n"\
"                 }\n"\
"\n"\
"               }; //ws.onmessage\n"\
"            \n"\
"            // close websocket\n"\
"               ws.onclose = function() { \n"\
"                   document.getElementById(\"canvas7670\").style.visibility = \"hidden\";\n"\
"                   document.getElementById(\"connecting\").style.visibility = \"visible\";\n"\
"               }; //ws.onclose\n"\
"\n"\
"               // websocket error handling\n"\
"               ws.onerror = function(evt) {\n"\
"                   document.getElementById(\"canvas7670\").style.visibility = \"hidden\";\n"\
"                   document.getElementById(\"connecting\").style.visibility = \"visible\";\n"\
"                   document.getElementById(\"connecting\").innerText = \"Error \" + evt.data;\n"\
"                   document.getElementById(\"constatus\").innerText = \"\";\n"\
"               };\n"\
"     \n"\
"            } else {\n"\
"            // The browser doesn't support WebSocket\n"\
"                alert(\"WebSocket NOT supported by your Browser!\");\n"\
"            }\n"\
"        } // WebSocketCamera\n"\
"\n"\
"\n"\
"function onloadinit() {\n"\
"   camera_ip = location.hostname;\n"\
"   //alert(camera_ip);\n"\
"   init();\n"\
"}\n"\
"function init() {\n"\
"    document.getElementById(\"canvas7670\").style.visibility = \"hidden\";\n"\
"    document.getElementById(\"connecting\").style.visibility = \"visible\";\n"\
"    initCanvas();\n"\
"    initWebSocket(); \n"\
"}\n"\
"\n"\
"function initCanvas() {\n"\
"    var canvas = document.getElementById(\"canvas-QQQ-VGA\");\n"\
"    var ctx = canvas.getContext(\"2d\");\n"\
"    ctx.font = \"10px Comic Sans MS\";\n"\
"    ctx.fillStyle = \"#FF0000\";\n"\
"    ctx.textAlign = \"center\";\n"\
"    ctx.fillText(\"80 x 60\", canvas.width/2, canvas.height/2);    \n"\
"\n"\
"    canvas = document.getElementById(\"canvas-QQ-VGA\");\n"\
"    ctx = canvas.getContext(\"2d\");\n"\
"    ctx.font = \"10px Comic Sans MS\";\n"\
"    ctx.fillStyle = \"#FF0000\";\n"\
"    ctx.textAlign = \"center\";\n"\
"    ctx.fillText(\"160 x 120\", canvas.width/2, canvas.height/2);    \n"\
"\n"\
"    canvas = document.getElementById(\"canvas-Q-VGA\");\n"\
"    ctx = canvas.getContext(\"2d\");\n"\
"    ctx.font = \"10px Comic Sans MS\";\n"\
"    ctx.fillStyle = \"#FF0000\";\n"\
"    ctx.textAlign = \"center\";\n"\
"    ctx.fillText(\"320 x 240\", canvas.width/2, canvas.height/2);    \n"\
"\n"\
"/*\n"\
"    canvas = document.getElementById(\"canvas-VGA\");\n"\
"    ctx = canvas.getContext(\"2d\");\n"\
"    ctx.font = \"10px Comic Sans MS\";\n"\
"    ctx.fillStyle = \"#FF0000\";\n"\
"    ctx.textAlign = \"center\";\n"\
"    ctx.fillText(\"640 x 480\", canvas.width/2, canvas.height/2);    \n"\
"*/    \n"\
"\n"\
"}\n"\
"\n"\
"//https://github.com/ThingPulse/minigrafx/issues/8\n"\
"function display(pixels, pixelcount, flag) {\n"\
"    //alert('display'); \n"\
"    var i = 0;\n"\
"    for(y=0; y < yres; y++) {\n"\
"       for(x=0; x < xres; x++)\n"\
"       { \n"\
"           i = (y * xres + x) << 1;\n"\
"           pixel16 = (0xffff & pixels[i]) | ((0xffff & pixels[i+1]) << 8);\n"\
"           imgData.data[ln+0] = ((((pixel16 >> 11) & 0x1F) * 527) + 23) >> 6;\n"\
"           imgData.data[ln+1] = ((((pixel16 >> 5) & 0x3F) * 259) + 33) >> 6;\n"\
"           imgData.data[ln+2] = (((pixel16 & 0x1F) * 527) + 23) >> 6;  \n"\
"           imgData.data[ln+3] = (0xFFFFFFFF) & 255;\n"\
"           ln += 4;\n"\
"       }\n"\
"    }\n"\
"    \n"\
"    if (flag == 0xFF) { // last block\n"\
"       ln = 0;        \n"\
"       ctx.putImageData(imgData,0,0);\n"\
"       ws.send(\"next-frame\");    \n"\
"    }\n"\
"    \n"\
" }\n"\
"\n"\
"function reset()\n"\
"{\n"\
"   r = 0;\n"\
"   capturecount = 1;\n"\
"   ln = 0;\n"\
"   flag = 0;\n"\
"   xres = 0;\n"\
"   yres = 0;\n"\
"   //gcanvasid = \"\";    \n"\
"   initCanvas();\n"\
"}\n"\
"\n"\
"function setip(whichip) {\n"\
"    if (gcanvasid != null && gcanvasid != \"\") {  \n"\
"       camera_ip = document.getElementById(whichip).innerText;\n"\
"       init();\n"\
"       initCanvas();\n"\
"       capture(gcanvasid);\n"\
"    }\n"\
"}\n"\
"\n"\
"function capture(canvasid)\n"\
"{\n"\
"    if (ws.readyState != 1) {\n"\
"    //    alert(\"ws.readyState \" + ws.readyState);    \n"\
"        return;      \n"\
"    }\n"\
" \n"\
"    reset();    \n"\
"    gcanvasid = canvasid;    \n"\
"    canvas = document.getElementById(canvasid);\n"\
"    ctx = canvas.getContext('2d');\n"\
"    if (canvasid.indexOf(\"canvas-VGA\", 0) != -1) {\n"\
"        xres = 640;\n"\
"        yres = 60;\n"\
"    } else if (canvasid.indexOf(\"canvas-Q-VGA\", 0) != -1) {\n"\
"        xres = 320;\n"\
"        yres = 120;\n"\
"    } else if (canvasid.indexOf(\"canvas-QQ-VGA\", 0) != -1) {\n"\
"        xres = 160;\n"\
"        yres = 120;\n"\
"    } else if (canvasid.indexOf(\"canvas-QQQ-VGA\", 0) != -1) {\n"\
"        xres = 80;\n"\
"        yres = 60;\n"\
"    }\n"\
"    \n"\
"    imgData = ctx.createImageData(canvas.width, canvas.height);\n"\
"    for (var i=0;i<imgData.data.length;i+=4)\n"\
"    {\n"\
"        imgData.data[i+0]=0xCC;\n"\
"        imgData.data[i+1]=0xCC;\n"\
"        imgData.data[i+2]=0xCC;\n"\
"        imgData.data[i+3]=255;\n"\
"    }\n"\
"    ctx.putImageData(imgData, canvas.width, canvas.height);\n"\
"    ws.send(canvasid);    \n"\
"}\n"\
"\n"\
"</script>\n"\
"\n"\
"<body onload=\"onloadinit()\">\n"\
"\n"\
"<div valign=center align=center style=\"\n"\
"    display: inline-block;\n"\
"    position: fixed;\n"\
"    top: 0;\n"\
"    bottom: 0;\n"\
"    left: 0;\n"\
"    right: 0;\n"\
"    width: 200px;\n"\
"    height: 100px;\n"\
"    margin: auto;\n"\
"    background-color: #FFFFFF;\" id=\"connecting\">Connecting Camera ...\n"\
"</div>\n"\
"\n"\
"<center> <h1> ESP32-OV7670 Websocket Video Camera </h1> </center>\n"\
"\n"\
"\n"\
"<table align=center valign=center id=\"canvas7670\">\n"\
"    <tr> \n"\
"        <td valign=\"bottom\">    \n"\
"<canvas id=\"canvas-QQQ-VGA\" width=\"80\" height=\"60\" style=\"cursor:crosshair;border:1px solid #FFFF00;\" onclick=\"capture('canvas-QQQ-VGA')\">\n"\
"Your browser does not support the HTML5 canvas tag.\n"\
"</canvas>\n"\
"        </td>\n"\
"\n"\
"        <td valign=\"bottom\">    \n"\
"<canvas id=\"canvas-QQ-VGA\" width=\"160\" height=\"120\" style=\"cursor:crosshair;border:1px solid #00FF00;\" onclick=\"capture('canvas-QQ-VGA')\">\n"\
"Your browser does not support the HTML5 canvas tag.\n"\
"</canvas>\n"\
"        </td>\n"\
"\n"\
"        <td valign=\"bottom\">\n"\
"<canvas id=\"canvas-Q-VGA\" width=\"320\" height=\"240\" style=\"cursor:crosshair;border:1px solid #0000FF;\" onclick=\"capture('canvas-Q-VGA')\">\n"\
"Your browser does not support the HTML5 canvas tag.\n"\
"</canvas>\n"\
"        </td>\n"\
"<!--\n"\
"        <td valign=\"bottom\">\n"\
"<canvas id=\"canvas-VGA\" width=\"640\" height=\"480\" style=\"cursor:crosshair;border:1px solid #FF00FF;\" onclick=\"capture('canvas-VGA')\">\n"\
"Your browser does not support the HTML5 canvas tag.\n"\
"</canvas>\n"\
"        </td>\n"\
"-->  \n"\
"    </tr>\n"\
"\n"\
"    <tr> \n"\
"        <td align=center>    \n"\
"            QQQ-VGA     <BR>\n"\
"        </td>\n"\
"\n"\
"        <td align=center>    \n"\
"            QQ-VGA     <BR>\n"\
"        </td>\n"\
"    \n"\
"        <td align=center>\n"\
"            Q-VGA     <BR>\n"\
"        </td>\n"\
"    \n"\
"<!--\n"\
"        <td align=center>    \n"\
"            VGA     <BR>\n"\
"        </td>\n"\
"-->  \n"\
"    </tr>\n"\
"\n"\
"\n"\
"</table>\n"\
"<BR><BR>\n"\
"<table width=30% align=center bgcolor=\"#FFFF00\" >\n"\
" <tr align=center style=\"color: #fff; background: black;\"> \n"\
"   <td id=\"constatus\" colspan=2>Websocket not connected</td> \n"\
" </tr>\n"\
"\n"\
" <tr align=center style=\"color: #fff; background: black;\"> \n"\
"   <td>AP IP </td> \n"\
"   <td>WiFi IP</td> \n"\
" </tr>\n"\
"\n"\
" <tr align=center bgcolor=\"#FFF\"> \n"\
"   <td id=\"ap-ip\" style=\"cursor:pointer\" onclick=\"setip('ap-ip')\">192.168.4.1</td> \n"\
"   <td id=\"wifi-ip\" style=\"cursor:pointer\" onclick=\"setip('wifi-ip')\"></td> \n"\
" </tr>\n"\
"         \n"\
"</table> \n"\
"\n"\
"\n"\
"</body>\n"\
"</html>\n"\
"\n";

