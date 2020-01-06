//Original LFU Information

/**
 * Copyright (c) 2018 Inria
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met: redistributions of source code must retain the above copyright
 * notice, this list of conditions and the following disclaimer;
 * redistributions in binary form must reproduce the above copyright
 * notice, this list of conditions and the following disclaimer in the
 * documentation and/or other materials provided with the distribution;
 * neither the name of the copyright holders nor the names of its
 * contributors may be used to endorse or promote products derived from
 * this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * Authors: Daniel Carvalho
 */


//MOD LFU Information
/**
 * 2019 by AirLight(https://github.com/FalsitaFine)
*/


#include "mem/cache/replacement_policies/lfu_mod.hh"

#include <cassert>
#include <memory>
#include <iostream>

#include "params/LFUMODRP.hh"


int globalCounter = 0;
int doubleHit = 0;
int touchFlag = 0;

int hitFlagI1 = 0;
int missFlagI1 = 0;

int hitFlagD1 = 0;
int missFlagD1 = 0;


int hitFlagL2 = 0;
int missFlagL2 = 0;



#define RESTARTTHRESHOLD 1024
#define RANDOMINSEARTTHRESHOLD 64



LFUMODRP::LFUMODRP(const Params *p)
    : BaseReplacementPolicy(p)
{
}

void
LFUMODRP::invalidate(const std::shared_ptr<ReplacementData>& replacement_data)
const
{
    // Reset reference count
    std::static_pointer_cast<LFUMODReplData>(replacement_data)->refCount = 0;
    //std::cout << "INVALIDATE" <<std::endl;

}

void
LFUMODRP::touch(const std::shared_ptr<ReplacementData>& replacement_data) const
{
    // Update reference count
    std::static_pointer_cast<LFUMODReplData>(replacement_data)->refCount++;

    //std::cout << "TOUCH" <<std::endl;



    //std::cout << "TOUCH(L1)=====:(missFlagI,missFlagD,hitFlagI,hitFlagD): " <<missFlagI1<<","<<missFlagD1<<","<<hitFlagI1<<","<<hitFlagD1<<std::endl;
    //std::cout << "TOUCH(L2)=====:(missFlag,hitFlag): " <<missFlagL2<<","<<hitFlagL2<<std::endl;

    //if (touchFlag == 1){
    //std::cout << "TOUCH" <<std::endl;

/*
    if (hitFlag >= 1){
         //std::cout << "+++++++HITFLAG PASS: " << hitFlag << std::endl;
         hitFlag = 0;
         if (doubleHit == 1){
            globalCounter = 0;
            doubleHit = 0;
            //std::cout << "DOUBLE HIT DETECTED, G-COUNTER RESET TO 0, CURRENT G-COUNTER: " << globalCounter << std::endl;

         }else{
            doubleHit = 1;
            if (globalCounter > 1){
                globalCounter -= 2;
            }
            //std::cout << "HIT DETECTED, G-COUNTER REDUCED, CURRENT G-COUNTER: " << globalCounter <<std::endl;
         }
    }

    if (missFlag >= 1){
         //std::cout << "+++++++MISSFLAG PASS: " << missFlag << std::endl;
         missFlag = 0;
         doubleHit = 0;
         ++globalCounter;
         //std::cout << "MISS DETECTED, G-COUNTER INCREASED BY 1, CURRENT G-COUNTER: " << globalCounter << std::endl;

    }
*/
    /*

        if(doubleHit == 0){
            doubleHit = 1;
            if (globalCounter > 0){
                globalCounter--;
            }
            std::cout << "HIT DETECTED, G-COUNTER REDUCED BY 1 CURRENT G-COUNTER: " << globalCounter <<std::endl;
        }else{
            doubleHit = 0;
            globalCounter = 0;
            std::cout << "DOUBLE HIT DETECTED, G-COUNTER RESET TO 0 CURRENT G-COUNTER: " << globalCounter << std::endl;
        }
        //touchFlag = 0;

    */
    //}
}

void
LFUMODRP::reset(const std::shared_ptr<ReplacementData>& replacement_data) const
{
    // Reset reference count

    //std::cout << "RESET" <<std::endl;


    std::static_pointer_cast<LFUMODReplData>(replacement_data)->refCount = 1;
    //doubleHit = 0;

    //globalCounter += 1;
    //std::cout << "MISS DETECTED, G-COUNTER INCREASED BY 1, CURRENT G-COUNTER: " << globalCounter << std::endl;


}

ReplaceableEntry*
LFUMODRP::getVictim(const ReplacementCandidates& candidates) const
{
    // There must be at least one replacement candidate
    assert(candidates.size() > 0);
    ReplaceableEntry* victim;
    //touchFlag = 1;
    //std::cout << "START GET(L1):(missFlagI,missFlagD,hitFlagI,hitFlagD): " <<missFlagI1<<","<<missFlagD1<<","<<hitFlagI1<<","<<hitFlagD1<<std::endl;
    

    //std::cout << "START GET(L2):(missFlag,hitFlag): " <<missFlagL2<<","<<hitFlagL2<<std::endl;
    //std::cout << "Current GlobalCounter: " << globalCounter <<std::endl;

    //std::cout << "TEST PASS!!!" << std::endl;
    //Random Insert Mode


    if (hitFlagL2 >= 1){
         //std::cout << "+++++++HITFLAG PASS: " << hitFlag << std::endl;
         hitFlagL2 = 0;
         if (doubleHit == 1){
            globalCounter = 0;
            doubleHit = 0;
            //std::cout << "DOUBLE HIT DETECTED, G-COUNTER RESET TO 0, CURRENT G-COUNTER: " << globalCounter << std::endl;

         }else{
            doubleHit = 1;
            if (globalCounter > 1){
                globalCounter -= 2;
            }
            //std::cout << "HIT DETECTED, G-COUNTER REDUCED, CURRENT G-COUNTER: " << globalCounter <<std::endl;
         }
    }

    if (missFlagL2 >= 1){
         //std::cout << "+++++++MISSFLAG PASS: " << missFlag << std::endl;
         missFlagL2 = 0;
         doubleHit = 0;
         ++globalCounter;
         //std::cout << "MISS DETECTED, G-COUNTER INCREASED BY 1, CURRENT G-COUNTER: " << globalCounter << std::endl;

    }




    if (globalCounter > RANDOMINSEARTTHRESHOLD && globalCounter <= RESTARTTHRESHOLD){
        victim = candidates[0];
        //std::cout << "RANDOM INSERT HAPPEN" << std::endl;

    }

    //Flush Mode
    else if(globalCounter > RESTARTTHRESHOLD){
        std::cout << "FLUSH HAPPEN" << std::endl;
        globalCounter = 0;
        victim = candidates[0];
        for (const auto& candidate : candidates) {
            // Flush all counts
                std::static_pointer_cast<LFUMODReplData>(candidate->replacementData)->refCount = 0;
            }
    }

    //Normal Mode
    else{
        //std::cout << "COMMON INSERT HAPPEN" << std::endl;

        victim = candidates[0];
        for (const auto& candidate : candidates) {
            // Update victim entry if necessary
            if (std::static_pointer_cast<LFUMODReplData>(
                        candidate->replacementData)->refCount <
                    std::static_pointer_cast<LFUMODReplData>(
                        victim->replacementData)->refCount) {
                victim = candidate;
            }
        }
    }



    return victim;
}

std::shared_ptr<ReplacementData>
LFUMODRP::instantiateEntry()
{
    return std::shared_ptr<ReplacementData>(new LFUMODReplData());
}

LFUMODRP*
LFUMODRPParams::create()
{
    return new LFUMODRP(this);
}
