#include "status.hpp"

void Status::status(const dpp::slashcommand_t& event) {
    event.reply ("I'm alive, Sir!");
}