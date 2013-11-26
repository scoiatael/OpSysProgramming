#!/bin/sh
# RLIMIT_NPROC ustawia limit procesów użytkownika, więc dla lepszej kontroli trzeba uruchomić proces jako świeży user, najlepiej nieistniejący.
sudo -u \#1001 -g \#100 ./4 $@
