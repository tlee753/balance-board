#include "wii-balance.h"
#include <QApplication>
#include <unistd.h>

#include <iostream>
#include <string>
#include <chrono>
#include <deque>
#include <numeric>

#include <xwiimote.h>
#include <poll.h>

#include "wii-scale/XWiiMonitor.h"

std::unique_ptr<XWiiIface> board;

std::unique_ptr<XWiiIface> connect()
{
    XWiiMonitor monitor;
    std::unique_ptr<XWiiIface> device;

    while (device = monitor.Poll())
    {
        if (!device->HasBalanceBoard())
        {
            // Not a balance board, try the next device
            continue;
        }

        device->EnableBalanceBoard();
        return device;
    }

    return nullptr;
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    WiiBalance w;
    w.show();


    std::cout << "Wii-Scale started" << std::endl;

    bool ready = false;
    bool firstStep = false;
    std::deque<uint32_t> total;

    board = connect();

    std::cout << (board ? "CONNECTED" : "NO DEVICE FOUND") << std::endl;

    // Scale
    for (;;)
    {
        if (!board)
        {
            // Waiting for connection or command
            usleep(100000);
            continue;
        }

        // Post ready status once
        if (!ready)
        {
            firstStep = true;
            total.clear();

            ready = true;
        }

        struct xwii_event event;
        board->Dispatch(XWII_EVENT_WATCH | XWII_EVENT_BALANCE_BOARD, &event);

        if (event.type == XWII_EVENT_WATCH)
        {
            // Board has disconnected
            std::cout << "disconnected" << std::endl;

            board = nullptr;
            continue;
        }

        // Measure weight
        uint32_t totalWeight = 0;

        for (int i = 0; i < 4; i++)
        {
            totalWeight += event.v.abs[i].x;
            std::cout << i << ": " << event.v.abs[i].x << std::endl;
        }
        std::cout << "X Coord: " << (event.v.abs[0].x + event.v.abs[1].x) - (event.v.abs[2].x + event.v.abs[3].x) << std::endl;
        std::cout << "Y Coord: " << (event.v.abs[0].x + event.v.abs[2].x) - (event.v.abs[1].x + event.v.abs[3].x) << std::endl;
        std::cout << "Total: " << totalWeight << std::endl;
        std::cout << std::endl;

        if (firstStep)
        {
            firstStep = false;
        }

        total.push_back(totalWeight);
    }


    return a.exec();
}
