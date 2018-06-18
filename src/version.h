// Copyright (c) 2012 The Bitcoin developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.
#ifndef BITCOIN_VERSION_H
#define BITCOIN_VERSION_H

#include "clientversion.h"
#include <string>

//
// database format versioning
//
static const int DATABASE_VERSION = 70508;

//
// network protocol versioning
//
static const int PROTOCOL_VERSION = 70061;

// intial proto version, to be increased after version/verack negotiation
static const int INIT_PROTO_VERSION = 209;

// earlier versions not supported are disconnected
static const int MIN_PROTO_VERSION = 209;
static const int MIN_PEER_PROTO_VERSION = 70030;
static const int MIN_PEER_PROTO_VERSION_140 = 70040;
static const int MIN_PEER_PROTO_VERSION_143 = 70050;
static const int MIN_PEER_PROTO_VERSION_200 = 70060;
static const int MIN_PEER_PROTO_VERSION_210 = 70061;

//
static const int SOFT_FORK_VERSION_140 = 15999;
static const int SOFT_FORK_VERSION_143 = 65000;
static const int SOFT_FORK_VERSION_200 = 89500;
static const int SOFT_FORK_VERSION_210 = 122000;

// minimum peer version accepted by DarkSendPool
static const int MIN_POOL_PEER_PROTO_VERSION = 70061;
static const int MIN_INSTANTX_PROTO_VERSION = 70061;

// minimum peer version that can receive masternode payments
// V1 - Last protocol version before update
// V2 - Newest protocol version
static const int MIN_MASTERNODE_PAYMENT_PROTO_VERSION = 70061;

// nTime field added to CAddress, starting with this version;
// if possible, avoid requesting addresses nodes older than this
static const int CADDR_TIME_VERSION = 31402;

// only request blocks from nodes outside this range of versions
static const int NOBLKS_VERSION_START = 60002;
static const int NOBLKS_VERSION_END = 60006;

// BIP 0031, pong message, is enabled for all versions AFTER this one
static const int BIP0031_VERSION = 60000;

// "mempool" command, enhanced "getdata" behavior starts with this version:
static const int MEMPOOL_GD_VERSION = 60002;

#endif
