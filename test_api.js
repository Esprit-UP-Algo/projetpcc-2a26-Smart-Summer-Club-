var https = require('follow-redirects').https;
var fs = require('fs');

var options = {
    'method': 'POST',
    'hostname': 'jjk2wk.api.infobip.com',
    'path': '/email/4/messages',
    'headers': {
        'Authorization': 'App 3b62c5d8a3fa7ff2196c89d0b3abcf31-a9cbba3b-3ec0-4c51-a0eb-143bf2112e32',
        'Content-Type': 'application/json',
        'Accept': 'application/json'
    },
    'maxRedirects': 20
};

var req = https.request(options, function (res) {
    var chunks = [];

    res.on("data", function (chunk) {
        chunks.push(chunk);
    });

    res.on("end", function (chunk) {
        var body = Buffer.concat(chunks);
        console.log(body.toString());
    });

    res.on("error", function (error) {
        console.error(error);
    });
});

var postData = JSON.stringify({
    "messages": [
        {
            "destinations": [
                {
                    "to": [
                        {
                            "destination": "omar.cherif@esprit.tn"
                        }
                    ]
                }
            ],
            "sender": "SummerClub@selfserve.worlds-connected.co",
            "content": {
                "subject": "omar ya bhi ",
                "text": "Hi omar, i hope you are doing well while you are reading this message!"
            }
        }
    ]
});

req.write(postData);

req.end();