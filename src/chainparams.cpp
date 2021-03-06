// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2012 The Bitcoin developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "assert.h"

#include "chainparams.h"
#include "main.h"
#include "util.h"

#include <boost/assign/list_of.hpp>

using namespace boost::assign;

struct SeedSpec6 {
    uint8_t addr[16];
    uint16_t port;
};

#include "chainparamsseeds.h"

// Convert the pnSeeds6 array into usable address objects.
static void convertSeed6(std::vector<CAddress> &vSeedsOut, const SeedSpec6 *data, unsigned int count)
{
    // It'll only connect to one or two seed nodes because once it connects,
    // it'll get a pile of addresses with newer timestamps.
    // Seed nodes are given a random 'last seen time' of between one and two
    // weeks ago.
    const int64_t nOneWeek = 7*24*60*60;
    for (unsigned int i = 0; i < count; i++)
    {
        struct in6_addr ip;
        memcpy(&ip, data[i].addr, sizeof(ip));
        CAddress addr(CService(ip, data[i].port));
        addr.nTime = GetTime() - GetRand(nOneWeek) - nOneWeek;
        vSeedsOut.push_back(addr);
    }
}

//
// Main network
//
class CMainParams : public CChainParams {
public:
    CMainParams()
    {
        networkID = CChainParams::MAIN;
        strNetworkID = "main";

        // The message start string is designed to be unlikely to occur in normal data.
        // The characters are rarely used upper ASCII, not valid as UTF-8, and produce
        // a large 4-byte int at any alignment.
        pchMessageStart[0] = 0x42;
        pchMessageStart[1] = 0xa4;
        pchMessageStart[2] = 0xc5;
        pchMessageStart[3] = 0x2b;

        vAlertPubKey = ParseHex("04f35675a3f24fd836bec1735d65b0dbc7f8cd491423ef50cdb9e1aab39721d4a752d9777be7d699e26f4c6db186e883c87b2fad0428ae216faf5bed61cf8d317f");
        nDefaultPort = 8710;
        nRPCPort = 8101;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 20);
        bnProofOfStakeLimit = CBigNum(~uint256(0) >> 20);

        const char* pszTimestamp = "https://news.bitcoin.com/mark-karpeles-wants-resurrect-mt-gox-ico";
        std::vector<CTxIn> vin;
        vin.resize(1);
        vin[0].scriptSig = CScript() << 0 << CBigNum(42) << vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
        std::vector<CTxOut> vout;
        vout.resize(1);
        // vout[0].nValue = 0;
        vout[0].SetEmpty();
        CTransaction txNew(1, 1511096400, vin, vout, 0);
        genesis.vtx.push_back(txNew);
        genesis.hashPrevBlock = 0;
        genesis.hashMerkleRoot = genesis.BuildMerkleTree();
        genesis.nVersion = 1;
        genesis.nTime    = 1511096400; // Mon, 01 May 2017 00:00:00 GMT
        genesis.nBits    = bnProofOfWorkLimit.GetCompact();
        genesis.nNonce   = 1774559;

        /** Genesis Block MainNet */
        /*
        Hashed MainNet Genesis Block Output
        block.hashMerkleRoot == 0xc08b7e10f87514a98554968c06868edbdb6d97ad560112b3c1f9c90c09656d95
        block.nTime = 1511096400
        block.nNonce = 1774559
        block.GetHash = 00001f66cb3ba8f5776cb750d621cb3390200580cc39f076b3f61efcf191fba0
        */
        hashGenesisBlock = genesis.GetHash();
        assert(hashGenesisBlock == uint256("0x000009e335cea03f1432c49c44893095f18e261c4d78de38882961f92f4b22c7"));
        assert(genesis.hashMerkleRoot == uint256("0xc08b7e10f87514a98554968c06868edbdb6d97ad560112b3c1f9c90c09656d95"));

        // DNS Seeding
        vSeeds.push_back(CDNSSeedData("monk1.cryptoservices.tk", "monk1.cryptoservices.tk"));
        vSeeds.push_back(CDNSSeedData("monk2.cryptoservices.tk", "monk2.cryptoservices.tk"));
        vSeeds.push_back(CDNSSeedData("monk3.cryptoservices.tk", "monk3.cryptoservices.tk"));
        vSeeds.push_back(CDNSSeedData("seed1", "seed1.monkey.vision"));
        vSeeds.push_back(CDNSSeedData("seed2", "seed2.monkey.vision"));
        vSeeds.push_back(CDNSSeedData("seed3", "seed3.monkey.vision"));

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,51);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,28);
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,55);
        base58Prefixes[EXT_PUBLIC_KEY] = list_of(0x04)(0x88)(0xB2)(0x1E).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = list_of(0x04)(0x88)(0xAD)(0xE4).convert_to_container<std::vector<unsigned char> >();

        convertSeed6(vFixedSeeds, pnSeed6_main, ARRAYLEN(pnSeed6_main));

        nPoolMaxTransactions = 3;
        strSporkKey = "0431a3e4fcb29011df5ac2e47e0da085f9378c7de8174cf9b7ccd8959235c4be2be224b5880c6036c5f7718c12c988c39db7f2af0e392748cca23726a4cfd97815";
        strDarksendPoolDummyAddress = "Mgn67cAEbNSs6Ajfq52HzNMbdtsxV9XHxL";
        nEndPoWBlock = 75000;
        nStartPoSBlock = 0;

        nStakeMinAge = 8 * 60 * 60; // 8 hours
        nStakeMaxAge = 2 * 24 * 60 * 60; // 48 hours
        nStakeMaxAgeV2 =  10 * 24 * 60 * 60; // 240 hours

        nMasternodeCountDrift = 20;
    }

    virtual const CBlock& GenesisBlock() const { return genesis; }

    virtual const vector<CAddress>& FixedSeeds() const {
        return vFixedSeeds;
    }
protected:
    CBlock genesis;
    vector<CAddress> vFixedSeeds;
};
static CMainParams mainParams;


//
// Testnet
//
class CTestNetParams : public CMainParams {
public:
    CTestNetParams()
    {
        networkID = CChainParams::TESTNET;
        strNetworkID = "test";
        pchMessageStart[0] = 0x2c;
        pchMessageStart[1] = 0xab;
        pchMessageStart[2] = 0x21;
        pchMessageStart[3] = 0xc3;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 16);
        bnProofOfStakeLimit = CBigNum(~uint256(0) >> 20);
        vAlertPubKey = ParseHex("0434ff6edbff4e2b6b1474e80c4436f5b266e292fd203fc8425c788688f96e89975c4ba08fb160181b56048d560e83b5ea8ac118a29f9d3b9f4ab90a6de23a817f");
        nDefaultPort = 8711;
        nRPCPort = 8102;
        strDataDir = "testnet";

        // Modify the testnet genesis block so the timestamp is valid for a later start.
        genesis.nTime    = 1511096400;
        genesis.nBits  = bnProofOfWorkLimit.GetCompact();
        genesis.nNonce = 1838579;

        /** Genesis Block TestNet */
        /*
        Hashed TestNet Genesis Block Output
        block.hashMerkleRoot == 0xc08b7e10f87514a98554968c06868edbdb6d97ad560112b3c1f9c90c09656d95
        block.nTime = 1511096400
        block.nNonce = 1838579
        block.GetHash = 0000ae1d0aaeda3c5554fc4d5192c481d002174e33985bb8c855edd899fd0346
        */
        hashGenesisBlock = genesis.GetHash();
        assert(hashGenesisBlock == uint256("0x00000faeefd0e5c19a761b91689dc00e46a43974faf3c82d75bf4f57a771d9bc"));

        vFixedSeeds.clear();
        vSeeds.clear();

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,127);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,196);
        base58Prefixes[SECRET_KEY]     = std::vector<unsigned char>(1,63);
        base58Prefixes[EXT_PUBLIC_KEY] = list_of(0x04)(0x35)(0x87)(0xCF).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = list_of(0x04)(0x35)(0x83)(0x94).convert_to_container<std::vector<unsigned char> >();

        nEndPoWBlock = 1000;
        nStakeMinAge = 20 * 60; // 20 mins

        nMasternodeCountDrift = 4;
        strSporkKey = "04bae79cbfbcc3c555643d371388bd02ade4c8b09d1529e191aa6e06becd4d3ab0fde31d320704d1bc6d5e33b107335aa41e3a89eec6b0dfce015c9ab37eee966c";
    }
};
static CTestNetParams testNetParams;

//
// Regression test
//
class CRegTestParams : public CTestNetParams {
public:
    CRegTestParams()
    {
        networkID = CChainParams::REGTEST;
        strNetworkID = "regtest";
        pchMessageStart[0] = 0x42;
        pchMessageStart[1] = 0xa4;
        pchMessageStart[2] = 0xc5;
        pchMessageStart[3] = 0x2b;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 1);
        genesis.nTime = 1511096400;
        genesis.nBits  = bnProofOfWorkLimit.GetCompact();
        genesis.nNonce = 8;
        hashGenesisBlock = genesis.GetHash();
        nDefaultPort = 10300;
        strDataDir = "regtest";

        /** Genesis Block TestNet */
        /*
        Hashed RegNet Genesis Block Output
        block.hashMerkleRoot == 0xc08b7e10f87514a98554968c06868edbdb6d97ad560112b3c1f9c90c09656d95
        block.nTime = 1493596890
        block.nNonce = 8
        block.GetHash = b772ef430a34e04f015ab7a4e4fbe2e882794a83b1dc0056573d74880649d073
        */
        // assert(hashGenesisBlock == hashRegNetGenesisBlock);

        vSeeds.clear();  // Regtest mode doesn't have any DNS seeds.
    }

    virtual bool RequireRPCPassword() const { return false; }
    virtual Network NetworkID() const { return CChainParams::REGTEST; }
};
static CRegTestParams regTestParams;

static CChainParams *pCurrentParams = &mainParams;

const CChainParams &Params() {
    return *pCurrentParams;
}

CChainParams& Params(CChainParams::Network network)
{
    switch (network) {
    case CChainParams::MAIN:
        return mainParams;
    case CChainParams::TESTNET:
        return testNetParams;
    case CChainParams::REGTEST:
        return regTestParams;
    default:
        assert(false && "Unimplemented network");
        return mainParams;
    }
}

void SelectParams(CChainParams::Network network) {
    switch (network) {
        case CChainParams::MAIN:
            pCurrentParams = &mainParams;
            break;
        case CChainParams::TESTNET:
            pCurrentParams = &testNetParams;
            break;
        case CChainParams::REGTEST:
            pCurrentParams = &regTestParams;
            break;
        default:
            assert(false && "Unimplemented network");
            return;
    }
}

bool SelectParamsFromCommandLine() {
    bool fRegTest = GetBoolArg("-regtest", false);
    bool fTestNet = GetBoolArg("-testnet", false);

    if (fTestNet && fRegTest) {
        return false;
    }

    if (fRegTest) {
        SelectParams(CChainParams::REGTEST);
    } else if (fTestNet) {
        SelectParams(CChainParams::TESTNET);
    } else {
        SelectParams(CChainParams::MAIN);
    }
    return true;
}

unsigned int CChainParams::StakeMaxAge() const
{
    if (nBestHeight >= SOFT_FORK_VERSION_200)
        return nStakeMaxAgeV2;
    else
        return nStakeMaxAge;
}
