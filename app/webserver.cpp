#include <SmingCore.h>
#include <Data/Stream/TemplateFlashMemoryStream.h>
#include <JsonObjectStream.h>

#include <webserver.h>
#include <configuration.h>
#include <Libraries/StepperDriver/src/DRV8825.h>

HttpServer server;
DRV8825 driver(200, 12, 14);
bool stepperStarted = false;
long stepperRevolutionsCount = 0;

IMPORT_FSTR(indexHtml, PROJECT_DIR "/clientApp/dist/index.html")

void moveStepperTask() {
    stepperStarted = true;

    driver.move(Settings.StepsPerRevolution * Settings.GearRatio * stepperRevolutionsCount);

    stepperStarted = false;
}

/*
 * Index page
 * */
void onIndex(HttpRequest &request, HttpResponse &response) {
    auto* tmpl = new TemplateFlashMemoryStream(indexHtml);
    response.sendNamedStream(tmpl); // will be automatically deleted
}

/*
 * Get/Post requests for configuration
 * */
void onConfiguration(HttpRequest &request, HttpResponse &response) {
    if (request.method == HTTP_POST) {

        if(request.getBodyStream() == nullptr) {
            response.code = HTTP_STATUS_BAD_REQUEST;
            return;
        }

        StaticJsonDocument<1024> root;
        if(!Json::deserialize(root, request.getBodyStream())) {
            response.code = HTTP_STATUS_BAD_REQUEST;
            return;
        }

        Json::serialize(root, Serial, Json::Pretty);

        Settings.GearRatio = root["gearRatio"];
        Settings.StepsPerRevolution = root["stepsPerRevolution"];

        Settings.save();
    } else {
        auto *stream = new JsonObjectStream();
        JsonObject json = stream->getRoot();

        json["stepsPerRevolution"] = Settings.StepsPerRevolution;
        json["gearRatio"] = Settings.GearRatio;

        response.sendDataStream(stream, MIME_JSON);
    }
}

/*
 * Stepper status
 * */
void onStatus(HttpRequest &request, HttpResponse &response) {
    auto *stream = new JsonObjectStream();
    JsonObject json = stream->getRoot();

    json["started"] = stepperStarted;
    json["stepperRevolutionsCount"] = stepperRevolutionsCount;

    response.sendDataStream(stream, MIME_JSON);
}

/*
 * Start stepper drive
 * */
void onMove(HttpRequest &request, HttpResponse &response) {
    if (request.method == HTTP_POST) {
        if(stepperStarted) {
            response.code = HTTP_STATUS_BAD_REQUEST;
            return;
        }

        if(request.getBodyStream() == nullptr) {
            response.code = HTTP_STATUS_BAD_REQUEST;
            return;
        }

        StaticJsonDocument<1024> root;
        if(!Json::deserialize(root, request.getBodyStream())) {
            response.code = HTTP_STATUS_BAD_REQUEST;
            return;
        }

        Json::serialize(root, Serial, Json::Pretty);

        stepperRevolutionsCount = root["count"];

        System.queueCallback(moveStepperTask);
    }
}


void onReset(HttpRequest &request, HttpResponse &response)
{
    if (request.method == HTTP_POST) {
        System.restart(1000);
    }
}

/*
 * Process js, css files
 * */
void onFile(HttpRequest &request, HttpResponse &response) {
    String file = request.uri.getRelativePath();

    if (file[0] == '.')
        response.code = HTTP_STATUS_FORBIDDEN;
    else {
        // response.setCache(86400, true); // It's important to use cache for better performance.
        response.sendFile(file);
    }
}

void startServer() {

    server.listen(80);

    //frontend virtual routing
    server.paths.set("/", onIndex);
    server.paths.set("/settings", onIndex);

    server.paths.set("/configuration", onConfiguration);
    server.paths.set("/reset", onReset);
    server.paths.set("/move", onMove);
    server.paths.set("/status", onStatus);

    server.paths.setDefault(onFile);

    server.setBodyParser(MIME_JSON, bodyToStringParser);

    driver.begin();
    driver.enable();
}