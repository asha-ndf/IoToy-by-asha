#include <WiFi.h>
#include <WebServer.h>
#include "webpages.h"
// 初期画面
void webRoot(void)
{
  // HTMLを組み立てる
  const String html = R"rawliteral(
<!DOCTYPE HTML>
<html>

<head>
    <meta charset="utf-8">
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <link href="https://cdn.jsdelivr.net/npm/bootstrap@5.0.2/dist/css/bootstrap.min.css" rel="stylesheet"
        integrity="sha384-EVSTQN3/azprG1Anm3QDgpJLIm9Nao0Yz1ztcQTwFspd3yD65VohhpuuCOmLASjC" crossorigin="anonymous">

    <script src="https://ajax.googleapis.com/ajax/libs/jquery/3.4.1/jquery.min.js"></script>
</head>

<body>
    <h1>制御ページ</h1>
    <p>MODE (<span id="modeValue"></span>)</p>
    <input type="range" min="0" max="10" step="1" class="form-range slider" id="slideBar"
        onchange="changeValue(this.value)" value=0 />
    <button class="carousel-control-prev" type="button" data-bs-target="#carouselExampleControls" data-bs-slide="prev">
        <span class="carousel-control-prev-icon" aria-hidden="true"></span>
        <span class="visually-hidden">Previous</span>
    </button>
    <button class="carousel-control-next" type="button" data-bs-target="#carouselExampleControls" data-bs-slide="next">
        <span class="carousel-control-next-icon" aria-hidden="true"></span>
        <span class="visually-hidden">Next</span>
    </button>
    </div>
    <ul class="list-group list-group-horizontal">
        <li class="list-group-item"><button type="button" class="btn btn-primary btn-lg cmode"
                onclick="changeValue(1)">　1　</button></li>
        <li class="list-group-item"><button type="button" class="btn btn-primary btn-lg cmode"
                onclick="changeValue(2)">　2　</button></li>
        <li class="list-group-item"><button type="button" class="btn btn-primary btn-lg cmode"
                onclick="changeValue(3)">　3　</button></li>
    </ul>
    <ul class="list-group list-group-horizontal">
        <li class="list-group-item"><button type="button" class="btn btn-primary btn-lg cmode"
                onclick="changeValue(4)">　4　</button></li>
        <li class="list-group-item"><button type="button" class="btn btn-primary btn-lg cmode"
                onclick="changeValue(5)">　5　</button></li>
        <li class="list-group-item"><button type="button" class="btn btn-primary btn-lg cmode"
                onclick="changeValue(6)">　6　</button></li>
    </ul>
    <ul class="list-group list-group-horizontal">
        <li class="list-group-item"><button type="button" class="btn btn-primary btn-lg cmode"
                onclick="changeValue(7)">　7　</button></li>
        <li class="list-group-item"><button type="button" class="btn btn-primary btn-lg cmode"
                onclick="changeValue(8)">　8　</button></li>
        <li class="list-group-item"><button type="button" class="btn btn-primary btn-lg cmode"
                onclick="changeValue(9)">　9　</button></li>
    </ul>
    <BR>
    <button type="button" class="btn btn-primary btn-lg confbtn" onclick="submitValue()">設定</button>
    <button type="button" class="btn btn-danger btn-lg confbtn" onclick="submitClose()">停止</button>
    <div class="spinner-border text-danger spinner-div" role="status" id="spinner">
        <span class="visually-hidden">Loading...</span>
    </div>
    <script>
        var mode = 0;
        var obj = document.getElementById("slideBar");
        var target = document.getElementById("modeValue");
        target.innerHTML = obj.value;
        obj.oninput = function () {
            obj.value = this.value;


        }
        function changeValue(val) {
            mode = val;
            if (val == 0) {
                target.innerText = "OFF";
            } else {
                target.innerHTML = val;
            }
        }
        function submitValue() {
            $("#spinner").show();
            $.ajax({
                type: 'GET',
                url: "/set?m=" + mode,
                complete: function () {
                    setTimeout(function () {
                        $("#spinner").hide(); //Request is complete so hide spinner
                    }, 500);
                }
            });
        }
        function submitClose() {
            $("#spinner").show();
            $.ajax({
                type: 'GET',
                url: "/set?m=0",
                complete: function () {
                    setTimeout(function () {
                        $("#spinner").hide(); //Request is complete so hide spinner
                    }, 500);
                }
            });
        }
    </script>
    <script src="https://cdn.jsdelivr.net/npm/bootstrap@5.0.2/dist/js/bootstrap.bundle.min.js"
        integrity="sha384-MrcW6ZMFYlzcLA8Nl+NtUVF0sA7MsXsP1UyJoMp4YLEuNSfAP+JcXn/tWtIaxVXM"
        crossorigin="anonymous"></script>
</body>

</html>
<style>
    html {
        font-family: Helvetica;
        display: inline-block;
        margin: 0px auto;
        text-align: center;
    }

    .slider {
        width: 70%;
    }

    .slider-block {
        display: flex;
        width: 100%;
    }

    .card {
        width: 100%;
        height: 200px;
        background: #3486eb;
        border: 1px solid #000;
    }

    .spinner-div {
        display: none;
        text-align: center;
        position: fixed;
        top: 0px;
        left: 0px;
    }

    .confbtn {
        width: 40%;
    }

    .carbtn {
        height: 10px;
    }

    .cbtn {
        height: 100px;
        width: 100px !important;
    }

    .list-group-item {
        width: 33%;
    }
</style>
)rawliteral";

  // HTMLを出力する
  server.send(200, "text/html", html);
}

void webMode(void)
{
  // 「/set?m=〇」の形でアクセスしてください。
  String json = "{'Error','invaild number'}";
  if (server.hasArg("m"))
  {
    // 「○」の値に応じて、Modeを変更する
    int input =  server.arg("m").toInt();
    for(int i=0;i<10;i++){
      if (i == input){
        nowmode = input;
        json ="{'Mode',";
        json.concat(String(input));
        json.concat("}");
      }
    }
  }
  server.send(200, "application/json", json);
}

// 存在しないアドレスが指定された時の処理
void web404(void)
{
  server.send(404, "application/json", "Not Found.");
}
