# KurisuBot

KurisuBot is a discord bot intent to run in a homelab server or similar. It is designed to be fast, reliable and with a small memory footprint. It is written in C++ and uses the discord API to interact with the server with the help of [D++](https://github.com/brainboxdotcc/DPP).

## Compiling and running

```bash
meson setup builddir
```

```bash
meson compile -C builddir && ./builddir/kurisubot
```

### Use clang format

```bash
clang-format -i src/*.cpp
```

## The bot token

The token is a secret key that allows the bot to connect to the discord server. Here, we use a file called `env.json` in the same folder the executable is in or pass it as an argument to the program.

`env.json` should look like this:

```json
{
    "token": "your_token_here"
}
```

You can also pass the token as an argument to the program:

```bash
./kurisubot your_token_here
```

## Running in the background

On linux systems:

```bash
sudo ./kurisubot & disown
```

## Dependencies

- [D++](https://github.com/brainboxdotcc/DPP)
- [The meson build system](https://mesonbuild.com/)

## System

Bot was tested on Ubuntu 22.04
Kernel: 6.5.0-26-generic

<img src="https://cdn.donmai.us/sample/43/f1/__makise_kurisu_steins_gate_and_1_more_drawn_by_moshimoshibe__sample-43f147a29eab006c16ff8a32ea9aa0b0.jpg" width="350px">