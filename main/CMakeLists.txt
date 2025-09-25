idf_component_register(SRCS "http_server.c" "main.c" "temperature_100k.c" "wifi_app.c" "http_server.c"
                    INCLUDE_DIRS "."
                    EMBED_FILES webpage/index.html webpage/favicon.ico webpage/app.js webpage/app.css webpage/jquery-3.3.1.min.js)