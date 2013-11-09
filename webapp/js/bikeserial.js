/**
Copyright 2012 Google Inc.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

     http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.

Author: name (email)
**/


var mapKey = "AIzaSyCPndpkMJ6A8UTSI4swRPiANyxReji5fKA";

const SENSOR_REFRESH_INTERVAL=200;

var hyperlapse;



(function() {
  
  var btnOpen=document.querySelector(".open");
  var btnClose=document.querySelector(".close");
  var logArea=document.querySelector(".log");
  var statusLine=document.querySelector("#status");
  
  var serial_devices=document.querySelector(".serial_devices");
  
  var logObj=function(obj) {
    console.log(obj);
  }
  var logSuccess=function(msg) {
    log("<span style='color: green;'>"+msg+"</span>");
  };
  var logError=function(msg) {
    statusLine.className="error";
    statusLine.textContent=msg;
    log("<span style='color: red;'>"+msg+"</span>");
  };
  var log=function(msg) {
    console.log(msg);
    logArea.innerHTML=msg+"<br/>"+logArea.innerHTML;
  };


  var startHyperlapse = function(){


    hyperlapse = new Hyperlapse(document.getElementById('panorama'), {
      width: 1280,
      height: 720,
      zoom: 1,
      use_lookat: false,
      elevation: 50,
      max_points: 300,
      distance_between_points: 1,
      millis: 1000
    });

    hyperlapse.onError = function(e) {
      console.log(e);
    };

    hyperlapse.onRouteComplete = function(e) {
              //directions_renderer.setDirections(e.response);
              alert( "ACABOU\nNumber of Points: "+ hyperlapse.length() );
              hyperlapse.load();
    };

    hyperlapse.onLoadComplete = function(e) {
      //hyperlapse.play();
      alert("pronto para iniciar!");
    };


    // Google Maps API stuff here...
    var directions_service = new google.maps.DirectionsService();

    var route = {
      request:{
        origin: new google.maps.LatLng(37.816480000000006,-122.47825,37),
        destination: new google.maps.LatLng(37.81195,-122.47773000000001),
        travelMode: google.maps.DirectionsTravelMode.DRIVING
      }
    };

    directions_service.route(route.request, function(response, status) {
      if (status == google.maps.DirectionsStatus.OK) {
        hyperlapse.generate( {route:response} );
      } else {
        console.log(status);
      }
    });




  };
  
  var init=function() {
    if (!serial_lib) throw "You must include serial.js before";

    flipState(true);
    btnOpen.addEventListener("click", openSerial);
    btnClose.addEventListener("click", closeSerial);
    //window.addEventListener("hashchange", changeTab);
    document.querySelector(".refresh").addEventListener("click", refreshPorts);

    refreshPorts();


    //TODO: carregar hyperlapse
    //TODO: carregar maps
    //TODO: carregar trajeto
    google.load("maps", "3", {other_params:'sensor=TRUE', callback: startHyperlapse }); 







  };

/*
  var initADKListeners=function() {

    addEventToElements("change", ".servos input[type='range']", function(e, c) {
        writeSerial("s"+c+convertToChars(parseInt(this.value)));
    });
    addEventToElements("change", ".leds input[type='range']", function(e, c) {
        this.nextSibling.textContent=this.value;
        writeSerial("c"+c+convertToChars(parseInt(this.value)));
    });
    addEventToElements("click", ".relays button", function(e, c) {
      var on=this.className.indexOf(" on");
      if (on>=0) {
        // turn it off
        this.className=this.className.substring(0, on);
        this.textContent="Off";
        writeSerial("t"+c+"0");
      } else {
        // turn it on
        this.className=this.className+" on";
        this.textContent="On";
        writeSerial("t"+c+"1");
      }
    });

    setInterval(function() { writeSerial("data"); }, SENSOR_REFRESH_INTERVAL);
  };

  var convertToChars=function(i) {
    var ch=i.toString(16);
    if (ch.length==1) return "0"+ch;
    return ""+ch;
  };
  


  */
  
  var addEventToElements=function(eventType, selector, listener) {
    var elems=document.querySelectorAll(selector);
    
    for (var i=0; i<elems.length; i++) {
      (function() {
        var c=i;
        elems[i].addEventListener(eventType, function(e) {
          listener.apply(this, [e, c]);
        });
      })();
    }
  };

  var flipState=function(deviceLocated) {
    btnOpen.disabled=!deviceLocated;
    btnClose.disabled=deviceLocated;
  };
  
  var refreshPorts=function() {
    while (serial_devices.options.length > 0)
      serial_devices.options.remove(0);
    
    serial_lib.getPorts(function(items) {
      logSuccess("got "+items.length+" ports");
      for (var i=0; i<items.length; i++) {
         serial_devices.options.add(new Option(items[i], items[i]));
         if (i==1 || /usb/i.test(items[i]) && /tty/i.test(items[i])) {
           serial_devices.selectionIndex=i;
           logSuccess("auto-selected "+items[i]);
         }
      }
    });
  };
  
  var openSerial=function() {
    var serialPort=serial_devices.options[serial_devices.options.selectedIndex].value;
    if (!serialPort) {
      logError("Invalid serialPort");
      return;
    }
    statusLine.className="on";
    statusLine.textContent="Connecting";
    flipState(true);
    serial_lib.openSerial(serialPort, onOpen);
  };
  
  var onOpen=function(cInfo) {
    logSuccess("Device found (connectionId="+cInfo.connectionId+")");
    flipState(false);
    statusLine.textContent="Connected";
    serial_lib.startListening(onRead);
  };
  
  var writeSerial=function(writeString) {
    if (!serial_lib.isConnected()) {
      return;
    }
    if (!writeString) {
      logError("Nothing to write");
      return;
    }
    if (writeString.charAt(writeString.length-1)!=='\n') {
      writeString+="\n"; 
    }
    serial_lib.writeSerial(writeString); 
  }
  
  var onRead=function(readData) {
    if (readData.indexOf("log:")>=0) {
      return;
    }
    var m=/([^:]+):([-]?\d+)(?:,([-]?\d+))?/.exec(readData);
    console.log(m);
    if (m && m.length>0) {
      switch (m[1]) {
        case "s": document.querySelector("#speed").textContent=convertSpeed(m[2]); break;
        case "d": document.querySelector("#distance").textContent=m[2]; break;
        case "t": document.querySelector("#time").textContent=m[2]; break;
      }
    }
  }
  
  var convertSpeed=function(temperatureFromArduino) {
    return Math.round(temperatureFromArduino)*3.6;
  };

  var closeSerial=function() {
   serial_lib.closeSerial(onClose);
  };
  
  var onClose = function(result) {
   flipState(true);
   statusLine.textContent="Hover here to connect";
   statusLine.className="";
  }
  init();
})();
