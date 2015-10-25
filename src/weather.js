var xhrRequest = function (url, type, callback) {
  var xhr = new XMLHttpRequest();
  xhr.onload = function () {
    callback(this.responseText);
  };
  xhr.open(type, url);
  xhr.send();
};


function locationSuccess(pos) {
  var url = 'http://api.openweathermap.org/data/2.5/weather?' + 
      'lat=' +  pos.coords.latitude + 
      '&lon=' + pos.coords.longitude +
      '&APPID=b942e843af5e470b264793c66ba09a0e';
  
  console.log('Retrieving weather info...');
  xhrRequest(url, 'GET',
    function(responseText) {
      var jsonresponse = JSON.parse(responseText);

      var temperature = Math.round(jsonresponse.main.temp - 273.15);
      var conditions = jsonresponse.weather[0].main;      
      console.log('Temperature is ' + temperature);
      console.log('Conditions are ' + conditions);
      
      var dictionary = {
        'KEY_TEMPERATURE': temperature,
        'KEY_CONDITIONS': conditions
      };
      
      Pebble.sendAppMessage(dictionary,
        function(e) {
          console.log('Weather info sent to Pebble successfully!');
        },
        function(e) {
          console.log('Error sending weather info to Pebble!');
        }
      );
    }
  );
}

function locationError(err) {
  console.log('Error requesting location!');
}

function getWeather() {
  navigator.geolocation.getCurrentPosition(
    locationSuccess,
    locationError,
    {timeout: 15000, maximumAge: 60000}
  );
}


// Event listeners
Pebble.addEventListener('ready', 
  function(e) {
    console.log('PebbleKit JS ready!');
    getWeather();
  }
);

Pebble.addEventListener('appmessage',
  function(e) {
    console.log('AppMessage received!');
    getWeather();
  }                     
);
