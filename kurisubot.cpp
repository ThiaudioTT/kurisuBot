#include <dpp/dpp.h>
#include <iostream>
#define PROJECT_NAME "kurisuBot"

std::string BOT_TOKEN = "";

int main(const int argc, const char **argv) {
  if (argc > 2) {
    std::cerr << "Usage: " << argv[0] << " [bot token]\n";
    return 1;
  }

  // Set bot token
  if (argc == 2) {
    BOT_TOKEN = argv[1];
    std::cout << "Successfully set bot token" << std::endl;
  } else {
    // get token from env.json
    std::cout << "No token provided, attempting to read from env.json"
              << std::endl;
    std::ifstream env_file("env.json");
    if (env_file.is_open()) {
      nlohmann::json env;
      env_file >> env;
      BOT_TOKEN = env["token"];
      std::cout << "Successfully read token from env.json" << std::endl;
    } else {
      std::cerr << "Failed to read from env.json"
                << std::endl;
      return 1;
    }
  }

  std::cout << "This is project " << PROJECT_NAME << ".\n";

  // Create bot
  dpp::cluster bot(BOT_TOKEN);

  // Set up logging
  bot.on_log(dpp::utility::cout_logger());

  // Set up event handlers
  bot.on_slashcommand([](const dpp::slashcommand_t &event) {
    if (event.command.get_command_name() == "ping") {
      event.reply("Pong!");
    }
  });

  // Register bot commands
  bot.on_ready([&bot](const dpp::ready_t &event) {
    if (dpp::run_once<struct register_bot_commands>()) {
      bot.global_command_create(
          dpp::slashcommand("ping", "Ping pong!", bot.me.id));
    }
  });


  // Start bot
  bot.start(dpp::st_wait);

  return 0;
}
