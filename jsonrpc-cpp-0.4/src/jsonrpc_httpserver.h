/*
 *  JsonRpc-Cpp - JSON-RPC implementation.
 *  Copyright (C) 2008-2011 Sebastien Vincent <sebastien.vincent@cppextrem.com>
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Lesser General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

/**
 * \file jsonrpc_httpserver.h
 * \brief JSON-RPC HTTP server.
 * \author Sebastien Vincent
 */

#ifndef JSONRPC_HTTPSERVER_H
#define JSONRPC_HTTPSERVER_H

#include <list>
#include <string>
#include <map>

#include "jsonrpc_common.h"
#include "jsonrpc_server.h"

namespace Json
{

  namespace Rpc
  {
    /**
     * \class HttpServer
     * \brief JSON-RPC HTTP server implementation.
     */
    class HttpServer : public Server
    {
      public:
        /**
         * \brief Constructor.
         * \param address network address or FQDN to bind
         * \param port local port to bind
         */
        HttpServer(const std::string& address, uint16_t port);

        /**
         * \brief Destructor.
         */
        virtual ~HttpServer();

        /**
         * \brief Receive data from the network and process it.
         * \param fd socket descriptor to receive data
         * \return true if message has been correctly received, processed and
         * response sent, false otherwise (mainly send/recv error)
         * \note This method will blocked until data comes.
         */
        virtual bool Recv(int fd);

        /**
         * \brief Send data.
         * \param fd file descriptor of the client TCP socket
         * \param data data to send
         * \return number of bytes sent or -1 if error
         */
        virtual ssize_t Send(int fd, const std::string& data);

        /**
         * \brief Wait message.
         *
         * This function do a select() on the socket and Process() immediately 
         * the JSON-RPC message.
         * \param ms millisecond to wait (0 means infinite)
         */
        virtual void WaitMessage(uint32_t ms);

        /**
         * \brief Put the TCP socket in LISTEN state.
         */
        bool Listen() const;

        /**
         * \brief Accept a new client socket.
         * \return -1 if error, 0 otherwise
         */
        bool Accept();
        
        /**
         * \brief Close listen socket and all client sockets.
         */
        void Close();

        /**
         * \brief Get the list of clients.
         * \return list of clients
         */
        const std::list<int> GetClients() const;

      private:
        /**
         * \brief List of client sockets.
         */
        std::list<int> m_clients;
        /**
         * \brief Map of client socket undealed messages.
         */
        std::map<int, std::string> m_httpmsgs;

        /**
         * \brief List of disconnected sockets to be purged.
         */
        std::list<int> m_purge;
    };

  } /* namespace Rpc */

} /* namespace Json */

#endif /* JSONRPC_HTTPSERVER_H */

