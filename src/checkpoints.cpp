// Copyright (c) 2009-2012 The Bitcoin developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <boost/assign/list_of.hpp> // for 'map_list_of()'
#include <boost/foreach.hpp>

#include "checkpoints.h"

#include "txdb.h"
#include "main.h"
#include "uint256.h"


static const int nCheckpointSpan = 5000;

namespace Checkpoints
{
    typedef std::map<int, uint256> MapCheckpoints;

    //
    // What makes a good checkpoint block?
    // + Is surrounded by blocks with reasonable timestamps
    //   (no blocks before with a timestamp after, none after with
    //    timestamp before)
    // + Contains no strange transactions
    //
    static MapCheckpoints mapCheckpoints =
        boost::assign::map_list_of
        ( 0,        Params().HashGenesisBlock() )
        ( 4500,     uint256("0x28370f64f653e242cb6d396e66b2fcf0a9c67567cf71a12c3ba67729ab47a9c6"))
        ( 10501,    uint256("0x0000000000006993c25060db05eb91c5d3011570d12dc78bbbd788a7aeed8743"))
        ( 10502,    uint256("0x44dc047eb8839e13e12e05d6044d868df61e40cc7c09d43ce2580ffc185df7be"))
        ( 20000,    uint256("0x9e4781446d683d5f9e8a1d258c1ef6682642200bf485924a2ad3e29849bd9655"))
        ( 30000,    uint256("0x0238931fe88d10f8ee20f4fccb4fce99e7d9ac9985eeb96195f2f3ee81c4afce"))
        ( 40000,    uint256("0x3ff7da9aac362b499abd28fe260a200828a761e124c13a8e68f31929d9fa0c32"))
        ( 50000,    uint256("0x614323e40a7dbe3dc34b1b624db961c5cab1d99c6440ddea0fb5504e4fc1afee"))
        ( 60000,    uint256("0xe6c9870f9874575934456949ae9ea1bbc76362c7e8674600a9efcf39d440e1cc"))
        ( 70000,    uint256("0x519767e8c3b0c9e94129e8a642f1dd65cbb93f9916184f319710d472b46576cb"))
        ( 80000,    uint256("0x0bf354b70339cfa3db8fceaf8576ba40ee762f8a2b0a7bc9781198cf342c1255"))
        ( 85000,    uint256("0xb04c7cc602fa65b849a4d59fe363aed9d23c0a4b4d34f14cf2fe0adc60e2dee3"))
    ;

    // TestNet has no checkpoints
    static MapCheckpoints mapCheckpointsTestnet;

    bool CheckHardened(int nHeight, const uint256& hash)
    {
        MapCheckpoints& checkpoints = (TestNet() ? mapCheckpointsTestnet : mapCheckpoints);

        MapCheckpoints::const_iterator i = checkpoints.find(nHeight);
        if (i == checkpoints.end()) return true;
        return hash == i->second;
    }

    int GetTotalBlocksEstimate()
    {
        MapCheckpoints& checkpoints = (TestNet() ? mapCheckpointsTestnet : mapCheckpoints);

        if (checkpoints.empty())
            return 0;
        return checkpoints.rbegin()->first;
    }

    CBlockIndex* GetLastCheckpoint(const std::map<uint256, CBlockIndex*>& mapBlockIndex)
    {
        MapCheckpoints& checkpoints = (TestNet() ? mapCheckpointsTestnet : mapCheckpoints);

        BOOST_REVERSE_FOREACH(const MapCheckpoints::value_type& i, checkpoints)
        {
            const uint256& hash = i.second;
            std::map<uint256, CBlockIndex*>::const_iterator t = mapBlockIndex.find(hash);
            if (t != mapBlockIndex.end())
                return t->second;
        }
        return NULL;
    }

    // Automatically select a suitable sync-checkpoint
    const CBlockIndex* AutoSelectSyncCheckpoint()
    {
        const CBlockIndex *pindex = pindexBest;
        // Search backward for a block within max span and maturity window
        while (pindex->pprev && pindex->nHeight + nCheckpointSpan > pindexBest->nHeight)
            pindex = pindex->pprev;
        return pindex;
    }

    // Check against synchronized checkpoint
    bool CheckSync(int nHeight)
    {
        const CBlockIndex* pindexSync = AutoSelectSyncCheckpoint();
        if (nHeight <= pindexSync->nHeight){
            return false;
        }
        return true;
    }
}
