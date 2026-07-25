const char* ssid = "=Your wifi's name goes here";
const char* password = "Your password goes here";

void root() {
  String business_name = preferences.getString("business", "The Corner Cafe");
  String specialty = preferences.getString("specialty", "Iced Lavender Latte - $5.50");
  String extra_message = preferences.getString("extra", "");
  String out_of = preferences.getString("outof", "Oat milk\nBlueberry muffins");

  String html = "<html><head><title>Sign Settings</title><style>";
  html += "body{ background-color: #B8F5CB; }";
  html += "form{ background-color: lightblue; height: max-content; width: 400px; padding: 40px; border-radius: 15px; box-shadow: 7px 7px 16px 4px rgb(60, 179, 113, 1); }";
  html += "input, textarea { margin-top: 12px; padding-top: 8px; border-radius: 5px; }";
  html += "label { display: block; text-align: left; margin-top: 12px; }";
  html += "button{ margin-top: 12px; background-color: lightgreen; border-radius: 12px; width: 90px; height: 50px; }";
  html += "</style></head><body>";
  if (server.hasArg("saved")) {
    html += "<p style='background:lightgreen; padding:10px; border-radius:8px; width:max-content; margin:auto;'>Saved!</p>";
  }
  html += "<center><form method='POST' action='/update'>";
  html += "<label style='text-align:center;'>Business Name: <br><input id='business' name='business' value='" +  business_name + "'></label><br>";
  html += "<label style='text-align:center;'>Today's Special item: <br><input id='specialty' name='specialty' value='" + specialty + "'></label><br>";
  html += "<label style='text-align:center;'>Extra message (optional): <br><input id='extra' name='extra' value='" + extra_message + "'></label><br>";
  html += "<label style='text-align:center;'>Out of (one item per line/ Max 4 items): <br><textarea name='outof' rows='4' cols='30'>"+out_of+"</textarea></label><br>";
  html += "<button type='submit'>Save</button>";
  html += "</form></center>";
  html += "</body></html>";

  server.send(200, "text/html", html);
}

void update() {
  String new_name = server.arg("business");
  String new_specialty = server.arg("specialty");
  String new_extra = server.arg("extra");
  String new_out_of = server.arg("outof");

  preferences.putString("business", new_name);
  preferences.putString("specialty", new_specialty);
  preferences.putString("extra", new_extra);
  preferences.putString("outof", new_out_of);


  drawscreen();
  server.sendHeader("Location", "/?saved=1");
  server.send(303);
}

void connect(void) {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  WiFi.setSleep(false);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print("not connected");
  }

  Serial.println();
  Serial.println(WiFi.localIP()); // the address you'll type into a phone browser
}
