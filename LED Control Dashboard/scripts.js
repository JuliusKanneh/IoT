document.getElementById('D1-on').addEventListener('click', function () {
    var ip = document.getElementById('ip').value;
    var url = "http://api.thingspeak.com/update?api_key=" + ip + "&field1=1";
    $.getJSON(url, function (data) {
        console.log(data);
    });
});

document.getElementById('D1-off').addEventListener('click', function () {
    var ip = document.getElementById('ip').value;
    var url = "http://api.thingspeak.com/update?api_key=" + ip + "&field1=0";
    $.getJSON(url, function (data) {
        console.log(data);
    });
});

document.getElementById('D2-on').addEventListener('click', function () {
    var ip = document.getElementById('ip').value;
    var url = "http://api.thingspeak.com/update?api_key=" + ip + "&field2=1";
    $.getJSON(url, function (data) {
        console.log(data);
    });
});

document.getElementById('D2-off').addEventListener('click', function () {
    var ip = document.getElementById('ip').value;
    var url = "http://api.thingspeak.com/update?api_key=" + ip + "&field2=0";
    $.getJSON(url, function (data) {
        console.log(data);
    });
});

document.getElementById('D3-on').addEventListener('click', function () {
    var ip = document.getElementById('ip').value;
    var url = "http://api.thingspeak.com/update?api_key=" + ip + "&field3=1";
    $.getJSON(url, function (data) {
        console.log(data);
    });
});

document.getElementById('D3-off').addEventListener('click', function () {
    var ip = document.getElementById('ip').value;
    var url = "http://api.thingspeak.com/update?api_key=" + ip + "&field3=0";
    $.getJSON(url, function (data) {
        console.log(data);
    });
});

document.write("Hello World");