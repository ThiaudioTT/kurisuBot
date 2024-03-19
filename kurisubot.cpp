#include <iostream>
#include <dpp/dpp.h>
#define PROJECT_NAME "kurisuBot"

const std::string BOT_TOKEN = "myToken!";

int main(int argc, char **argv)
{
    if (argc != 1)
    {
        std::cout << argv[0] << "takes no arguments.\n";
        return 1;
    }
    std::cout << "This is project " << PROJECT_NAME << ".\n";

    dpp::cluster bot(BOT_TOKEN);

    bot.on_log(dpp::utility::cout_logger());

    bot.on_slashcommand([](const dpp::slashcommand_t &event)
                        {
        if (event.command.get_command_name() == "ping") {
            event.reply("Pong!");
        } });

    bot.on_ready([&bot](const dpp::ready_t &event)
                 {
        if (dpp::run_once<struct register_bot_commands>()) {
            bot.global_command_create(dpp::slashcommand("ping", "Ping pong!", bot.me.id));
        } });

    bot.start(dpp::st_wait);

    return 0;
}
