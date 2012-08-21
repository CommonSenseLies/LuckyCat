/**
 * Created with JetBrains WebStorm.
 * User: lihex
 * Date: 12-8-16
 * Time: 下午5:33
 * To change this template use File | Settings | File Templates.
 */


require("../../system/Log");

module.exports = function (req, res, next) {
    var log = new Log("actor.changeEquipmentInfo");

    var chunks = [];
    req.on("data", function(chunk) {
        chunks.push(chunk);
    });
    req.on("end", function () {
        var info = JSON.parse(Buffer.concat(chunks));
        chunks = undefined;
        log.d("request:", info);

        var responseResult = function (ret) {
            var respData={};
            var result = ret.result;
            var out = ret.out;
            var header = info.header;
            var meta = info.meta;
            respData.heard = header;
            respData.meta = meta;
            respData.meta.out = out;
            respData.meta.result = result;
            log.d("responseResult", respData);
            res.write(JSON.stringify(respData));
            res.end();
        };

        if (info) {
            var uuid = info.header.token;
            require("../Actors").getActor(uuid, function(actor){
                if (actor != null){
                    var part = parseInt(info.meta.in.part);
                    var id = parseInt(info.meta.in.id);
                    actor.changeEquipment(part, id, responseResult);
                }
            });
        } else {
            next();
        }



    });
};