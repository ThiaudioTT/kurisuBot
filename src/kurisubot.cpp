#include <dpp/dpp.h>
#include <iostream>
#include "status.hpp"
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
    const std::string command = event.command.get_command_name();

    // TODO: automatically register commands
    if (command == "ping") 
      event.reply("Pong!");
    else if (command == "status") 
      Status::status(event);
      
  });

  // Register bot commands
  bot.on_ready([&bot](const dpp::ready_t &event) {
    if (dpp::run_once<struct register_bot_commands>()) {
      // TODO: automatically register commands
      bot.global_command_create(dpp::slashcommand("ping", "Ping pong!", bot.me.id));
      bot.global_command_create(dpp::slashcommand("status", "Get bot/homelab status", bot.me.id));
    }

    // todo: avoid using srand because it's not thread-safe
    // set custom status
    srand(time(NULL));
    /* Create a timer that runs every 1 hour (3600s), that sets the status */
    bot.start_timer([&bot](const dpp::timer& timer) {
      const std::vector<std::string> playing_list = {
        "Hearts of Iron IV",
        "with the API",
        "with the code",
        "with the database",
        "with the logs",
        "in the server",
        "in the cloud",
        "in the homelab",
      };

      const uint8_t index = rand() % playing_list.size();
      bot.set_presence(dpp::presence(dpp::ps_online, dpp::at_game, playing_list[index]));
    }, 3600);
  });


  // Start bot
  bot.start(dpp::st_wait);

  return 0;
}
