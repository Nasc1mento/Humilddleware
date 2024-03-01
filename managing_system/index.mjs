import express from "express"
import http from "http";

const app = express();
const port = 8080;

function adapt(distance) {
    if (distance > 75) {
        return 60;
    } else if (distance > 50) {
        return 45;
    } else if (distance > 25) {
        return 30;
    } else {
        return 15;
    }
}


app.get("/adaptation", (req, res) => {
    console.log("/adaptation");
    const distance = req.query.distance;
    const duty_cicle = adapt(distance);
    res.type("text");
    res.send(duty_cicle.toString());
});

http.createServer(app).listen(port);
console.log("Running");