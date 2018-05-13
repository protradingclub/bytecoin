// Copyright (c) 2012-2018, The CryptoNote developers, The Bytecoin developers.
// Licensed under the GNU Lesser General Public License. See LICENSE for details.

#include "MiningConfig.hpp"
#include "common/CommandLine.hpp"
#include "common/Ipv4Address.hpp"

#include <iostream>
#include <thread>

#include "CryptoNoteConfig.hpp"
#include "logging/ILogger.hpp"

using namespace bytecoin;

MiningConfig::MiningConfig(common::CommandLine &cmd)
    : bytecoinmobiled_ip("127.0.0.1"), bytecoinmobiled_port(RPC_DEFAULT_PORT), thread_count(std::thread::hardware_concurrency()) {
	if (const char *pa = cmd.get("--address"))
		mining_address = pa;
	if (const char *pa = cmd.get("--bytecoinmobiled-address")) {
		if (!common::parse_ip_address_and_port(pa, bytecoinmobiled_ip, bytecoinmobiled_port))
			throw std::runtime_error("Wrong address format " + std::string(pa) + ", should be ip:port");
	}
	if (const char *pa = cmd.get("--daemon-address", "Use --bytecoinmobiled-address instead")) {
		if (!common::parse_ip_address_and_port(pa, bytecoinmobiled_ip, bytecoinmobiled_port))
			throw std::runtime_error("Wrong address format " + std::string(pa) + ", should be ip:port");
	}
	if (const char *pa = cmd.get("--daemon-host", "Use --bytecoinmobiled-address instead"))
		bytecoinmobiled_ip = pa;
	if (const char *pa = cmd.get("--daemon-rpc-port", "Use --bytecoinmobiled-address instead"))
		bytecoinmobiled_port = boost::lexical_cast<uint16_t>(pa);
	if (const char *pa = cmd.get("--threads"))
		thread_count = boost::lexical_cast<size_t>(pa);
	if (const char *pa = cmd.get("--limit"))
		blocks_limit = boost::lexical_cast<size_t>(pa);
}
