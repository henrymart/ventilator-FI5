 
/*
 * Copyright (C) 2020 iCub Tech - Istituto Italiano di Tecnologia
 * Author:  Marco Accame
 * email:   marco.accame@iit.it
*/

#include "fi5app_tHMI.h"


// needed to show the name of the thread in uvision: keep it global out of any namespace
void t_HMI(void *p)
{
    vnt::os::Thread *t = reinterpret_cast<vnt::os::Thread*>(p);
    t->run();
}

// the very basic needed to start a thread. it may become a code template. for now we duplicate it.

namespace fi5app { namespace tHMI { 

    void startup(vnt::os::Thread *t, void *param);
    void onevent(vnt::os::Thread *t, vnt::os::EventMask eventmask, void *param);

    constexpr vnt::os::EventThread::Config tcfg { 
        settings.stacksize, 
        settings.priority, 
        startup,
        nullptr,
        settings.timeout,
        onevent,
        "t_HMI"
    };

    vnt::os::EventThread* thr = nullptr;

    bool start()
    {
        if(nullptr != thr)
        {   // i dont want to start twice
            return false;
        }

        thr = new vnt::os::EventThread;

        if(nullptr == thr)
        {
            return false;
        }

        return thr->start(tcfg, t_HMI);
    }
    
    vnt::os::Thread * thread()
    {
        return thr;
    }
    
    
    bool trigger(const EVT ev)
    {
        if(nullptr == thr)
        {
            return false;
        }
        return thr->setEvent(vnt::core::tointegral(ev));         
    }
       
}} // namespace fi5app { namespace tHMI { 


// - the code which specialises the thread HMI
//   i can put includes in here. it is not canonical but it more clear to show the actual dependencies

#include "vnt_bsp.h"
#include "vnt_bsp_trace.h"
#include "vnt_bsp_watchdog.h"
#include "vnt_os_Timer.h"
#include "vnt_app_theLEDmanager.h"


#if defined(APP_HMI_disable)
#else
#include "ewmain.h"
#include "ewrte.h"
#include "ew_bsp_system.h"
#include "ew_bsp_console.h"
#include "ew_bsp_clock.h"
#endif

#include "vnt_tools.h"
#undef HMI_PRINTSTATS

namespace fi5app { namespace tHMI {

vnt::os::Timer *tmrTICK = nullptr;
    
vnt::tools::PeriodValidator *periodVAL = nullptr;
  
void startup(vnt::os::Thread *t, void *param)
{
    vnt::core::TimeFormatter tf1(vnt::core::now());
    vnt::bsp::trace::puts("theScheduler @ " + tf1.to_string() + " has called startup() of thread " + std::string(t->getName()) + " w/ prio = " + std::to_string(vnt::core::tointegral(t->getPriority())));  
    
    static const std::initializer_list<vnt::bsp::LED> allleds = {vnt::bsp::LED::one};  
    vnt::app::theLEDmanager &theleds = vnt::app::theLEDmanager::getInstance();     
    theleds.init(allleds);    
    theleds.get(vnt::bsp::LED::one).pulse(vnt::core::time1second); 
    
#if defined(HMI_PRINTSTATS)      
    periodVAL = new vnt::tools::PeriodValidator;
    periodVAL->init({40*vnt::core::time1millisec, 80*vnt::core::time1millisec, 5*vnt::core::time1second, {30*vnt::core::time1millisec, 80*vnt::core::time1millisec, 1*vnt::core::time1millisec}} );
#endif
        
    tmrTICK = new vnt::os::Timer;
    
    tmrTICK->start({settings.periodOfTICK, {vnt::os::EventToThread(vnt::core::tointegral(EVT::tick), t)}, vnt::os::Timer::Mode::forever, 0});
    
    // anything else    
}



// keep it lean.
// you may add a histogram builder upon duration of events, maybe ...


// note: the data to be displayed by the hmi is prepared by the tCTRL and is updated by a call of
// function ....
    
void onevent(vnt::os::Thread *t, vnt::os::EventMask eventmask, void *param)
{
    vnt::bsp::watchdog::refresh();  
    
    if(0 == eventmask)
    {   // timeout ...         
        return;
    }

    if(true == vnt::core::binary::mask::check(eventmask, vnt::core::tointegral(EVT::tick)))
    {
#if defined(APP_HMI_disable)
        vnt::bsp::delay(10*vnt::core::time1millisec);
#else 
        
    #if defined(HMI_PRINTSTATS) 
        vnt::core::Time start = vnt::core::now();
    #endif
        
        EwProcess();
        
    #if defined(HMI_PRINTSTATS)         
        vnt::core::Time delta = 0;
        periodVAL->tick(vnt::core::now()-start, delta);
        // if we want we can print delta just now
        vnt::bsp::trace::puts(vnt::core::TimeFormatter(delta).to_string());
        if(true == periodVAL->report())
        {
            const vnt::tools::Histogram *h = periodVAL->histogram();
            h->getvalues();
            std::string str = "HMI histogram = ";
            for(int i=0; i<h->getvalues()->inside.size(); i++) { str += std::to_string(h->getvalues()->inside[i]); str += ", "; }
            vnt::bsp::trace::puts(str);             
        }
    #endif        
#endif        
//        
    }
   
    if(true == vnt::core::binary::mask::check(eventmask, vnt::core::tointegral(EVT::userBTN01)))
    {
//        vnt::bsp::trace::puts("@ " + vnt::core::TimeFormatter(vnt::core::now()).to_string() + " tHMI has retrieved sensor 1: " + 
//                              std::to_string(tp01.pressure) + "@" + vnt::core::TimeFormatter(tp01.timestamp).to_string()); 
 
    }  

    if(true == vnt::core::binary::mask::check(eventmask, vnt::core::tointegral(EVT::userBTN02)))
    {
//        vnt::bsp::trace::puts("@ " + vnt::core::TimeFormatter(vnt::core::now()).to_string() + " tHMI has retrieved sensor 2: " + 
//                              std::to_string(tp02.pressure) + "@" + vnt::core::TimeFormatter(tp02.timestamp).to_string());    
    }    
 
    
}


}} // namespace fi5app { namespace tHMI {


// --------------------------------------------------------------------------------------------------------------------
// - end-of-file (leave a blank line after)
// --------------------------------------------------------------------------------------------------------------------


