/* NOTE(casey): 

   This code is a garbage hack that you shouldn't use unless you specifically knew why
   you thought it was going to help you with something.  And never, ever, EVER blame
   me if it messes something up, because it is totally your fault.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <memory.h>
#include <math.h>

#define internal static
#define ArrayCount(a) (sizeof(a)/sizeof((a)[0]))
typedef double f64;
typedef unsigned long long u64;

struct counter_spec
{
    char *ID;
    char *Description;
};

struct counter_stat
{
    u64 Value;
};

internal counter_spec
CounterSpecs[] =
{
    {"cycles", ""},
    {"instructions", ""},
    {"l1d.replacement", "L1D data line replacements"},
    {"l1d_pend_miss.fb_full", "Number of times a request needed a FB entry but there was no entry available for it. That is the FB unavailability was dominant reason for blocking the request. A request includes cacheable/uncacheable demands that is load, store or SW prefetch"},
    {"l1d_pend_miss.pending", "L1D miss outstandings duration in cycles"},
    {"l1d_pend_miss.pending_cycles", "Cycles with L1D load Misses outstanding"},
    {"l1d_pend_miss.pending_cycles_any", "Cycles with L1D load Misses outstanding from any thread on physical core"},
    {"l2_lines_in.all", "L2 cache lines filling L2"},
    {"l2_lines_out.non_silent", "Counts the number of lines that are evicted by L2 cache when triggered by an L2 cache fill. Those lines are in Modified state. Modified lines are written back to L3"},
    {"l2_lines_out.silent", "Counts the number of lines that are silently dropped by L2 cache when triggered by an L2 cache fill. These lines are typically in Shared or Exclusive state. A non-threaded event"},
    {"l2_lines_out.useless_hwpf", "Counts the number of lines that have been hardware prefetched but not used and now evicted by L2 cache"},
    {"l2_lines_out.useless_pref", "Counts the number of lines that have been hardware prefetched but not used and now evicted by L2 cache"},
    {"l2_rqsts.all_code_rd", "L2 code requests"},
    {"l2_rqsts.all_demand_data_rd", "Demand Data Read requests"},
    {"l2_rqsts.all_demand_miss", "Demand requests that miss L2 cache"},
    {"l2_rqsts.all_demand_references", "Demand requests to L2 cache"},
    {"l2_rqsts.all_pf", "Requests from the L1/L2/L3 hardware prefetchers or Load software prefetches"},
    {"l2_rqsts.all_rfo", "RFO requests to L2 cache"},
    {"l2_rqsts.code_rd_hit", "L2 cache hits when fetching instructions, code reads"},
    {"l2_rqsts.code_rd_miss", "L2 cache misses when fetching instructions"},
    {"l2_rqsts.demand_data_rd_hit", "Demand Data Read requests that hit L2 cache"},
    {"l2_rqsts.demand_data_rd_miss", "Demand Data Read miss L2, no rejects"},
    {"l2_rqsts.miss", "All requests that miss L2 cache"},
    {"l2_rqsts.pf_hit", "Requests from the L1/L2/L3 hardware prefetchers or Load software prefetches that hit L2 cache"},
    {"l2_rqsts.pf_miss", "Requests from the L1/L2/L3 hardware prefetchers or Load software prefetches that miss L2 cache"},
    {"l2_rqsts.references", "All L2 requests"},
    {"l2_rqsts.rfo_hit", "RFO requests that hit L2 cache"},
    {"l2_rqsts.rfo_miss", "RFO requests that miss L2 cache"},
    {"l2_trans.l2_wb", "L2 writebacks that access L2 cache"},
    {"longest_lat_cache.miss", "Core-originated cacheable demand requests missed L3 Spec update: SKL057"},
    {"longest_lat_cache.reference", "Core-originated cacheable demand requests that refer to L3 Spec update: SKL057"},
    {"mem_inst_retired.all_loads", "All retired load instructions Supports address when precise (Precise event)"},
    {"mem_inst_retired.all_stores", "All retired store instructions Supports address when precise (Precise event)"},
    {"mem_inst_retired.lock_loads", "Retired load instructions with locked access Supports address when precise (Precise event)"},
    {"mem_inst_retired.split_loads", "Retired load instructions that split across a cacheline boundary Supports address when precise (Precise event)"},
    {"mem_inst_retired.split_stores", "Retired store instructions that split across a cacheline boundary Supports address when precise (Precise event)"},
    {"mem_inst_retired.stlb_miss_loads", "Retired load instructions that miss the STLB Supports address when precise (Precise event)"},
    {"mem_inst_retired.stlb_miss_stores", "Retired store instructions that miss the STLB Supports address when precise (Precise event)"},
    {"mem_load_l3_hit_retired.xsnp_hit", "Retired load instructions which data sources were L3 and cross-core snoop hits in on-pkg core cache Supports address when precise (Precise event)"},
    {"mem_load_l3_hit_retired.xsnp_hitm", "Retired load instructions which data sources were HitM responses from shared L3 Supports address when precise (Precise event)"},
    {"mem_load_l3_hit_retired.xsnp_miss", "Retired load instructions which data sources were L3 hit and cross-core snoop missed in on-pkg core cache Supports address when precise (Precise event)"},
    {"mem_load_l3_hit_retired.xsnp_none", "Retired load instructions which data sources were hits in L3 without snoops required Supports address when precise (Precise event)"},
    {"mem_load_misc_retired.uc", "Retired instructions with at least 1 uncacheable load or lock Supports address when precise (Precise event)"},
    {"mem_load_retired.fb_hit", "Retired load instructions which data sources were load missed L1 but hit FB due to preceding miss to the same cache line with data not ready Supports address when precise (Precise event)"},
    {"mem_load_retired.l1_hit", "Retired load instructions with L1 cache hits as data sources Supports address when precise (Precise event)"},
    {"mem_load_retired.l1_miss", "Retired load instructions missed L1 cache as data sources Supports address when precise (Precise event)"},
    {"mem_load_retired.l2_hit", "Retired load instructions with L2 cache hits as data sources Supports address when precise (Precise event)"},
    {"mem_load_retired.l2_miss", "Retired load instructions missed L2 cache as data sources Supports address when precise (Precise event)"},
    {"mem_load_retired.l3_hit", "Retired load instructions with L3 cache hits as data sources Supports address when precise (Precise event)"},
    {"mem_load_retired.l3_miss", "Retired load instructions missed L3 cache as data sources Supports address when precise (Precise event)"},
    {"offcore_requests.all_data_rd", "Demand and prefetch data reads"},
    {"offcore_requests.all_requests", "Any memory transaction that reached the SQ"},
    {"offcore_requests.demand_code_rd", "Cacheable and noncachaeble code read requests"},
    {"offcore_requests.demand_data_rd", "Demand Data Read requests sent to uncore"},
    {"offcore_requests.demand_rfo", "Demand RFO requests including regular RFOs, locks, ItoM"},
    {"offcore_requests_buffer.sq_full", "Offcore requests buffer cannot take more entries for this thread core"},
    {"offcore_requests_outstanding.all_data_rd", "Offcore outstanding cacheable Core Data Read transactions in SuperQueue (SQ), queue to uncore"},
    {"offcore_requests_outstanding.cycles_with_data_rd", "Cycles when offcore outstanding cacheable Core Data Read transactions are present in SuperQueue (SQ), queue to uncore"},
    {"offcore_requests_outstanding.cycles_with_demand_code_rd", "Cycles with offcore outstanding Code Reads transactions in the SuperQueue (SQ), queue to uncore"},
    {"offcore_requests_outstanding.cycles_with_demand_data_rd", "Cycles when offcore outstanding Demand Data Read transactions are present in SuperQueue (SQ), queue to uncore"},
    {"offcore_requests_outstanding.cycles_with_demand_rfo", "Cycles with offcore outstanding demand rfo reads transactions in SuperQueue (SQ), queue to uncore"},
    {"offcore_requests_outstanding.demand_code_rd", "Offcore outstanding Code Reads transactions in the SuperQueue (SQ), queue to uncore, every cycle"},
    {"offcore_requests_outstanding.demand_data_rd", "Offcore outstanding Demand Data Read transactions in uncore queue"},
    {"offcore_requests_outstanding.demand_data_rd_ge_6", "Cycles with at least 6 offcore outstanding Demand Data Read transactions in uncore queue"},
    {"offcore_requests_outstanding.demand_rfo", "Offcore outstanding demand rfo reads transactions in SuperQueue (SQ), queue to uncore, every cycle"},
    {"offcore_response", "Offcore response can be programmed only with a specific pair of event select and counter MSR, and with specific event codes and predefine mask bit value in a dedicated MSR to specify attributes of the offcore transaction"},
    {"offcore_response.demand_code_rd.any_response", "Counts all demand code reads that have any response type"},
    {"offcore_response.demand_code_rd.l3_hit.any_snoop", "DEMAND_CODE_RD & L3_HIT & ANY_SNOOP"},
    {"offcore_response.demand_code_rd.l3_hit.snoop_hit_no_fwd", "Counts all demand code reads that hit in the L3 and the snoops to sibling cores hit in either E/S state and the line is not forwarded"},
    {"offcore_response.demand_code_rd.l3_hit.snoop_hitm", "DEMAND_CODE_RD & L3_HIT & SNOOP_HITM"},
    {"offcore_response.demand_code_rd.l3_hit.snoop_miss", "Counts all demand code reads that hit in the L3 and the snoops sent to sibling cores return clean response"},
    {"offcore_response.demand_code_rd.l3_hit.snoop_none", "DEMAND_CODE_RD & L3_HIT & SNOOP_NONE"},
    {"offcore_response.demand_code_rd.l3_hit.snoop_not_needed", "Counts all demand code reads that hit in the L3 and sibling core snoops are not needed as either the core-valid bit is not set or the shared line is present in multiple cores"},
    {"offcore_response.demand_code_rd.l3_hit.spl_hit", "DEMAND_CODE_RD & L3_HIT & SPL_HIT"},
    {"offcore_response.demand_code_rd.l3_hit_e.any_snoop", "DEMAND_CODE_RD & L3_HIT_E & ANY_SNOOP"},
    {"offcore_response.demand_code_rd.l3_hit_e.snoop_hit_no_fwd", "DEMAND_CODE_RD & L3_HIT_E & SNOOP_HIT_NO_FWD"},
    {"offcore_response.demand_code_rd.l3_hit_e.snoop_hitm", "DEMAND_CODE_RD & L3_HIT_E & SNOOP_HITM"},
    {"offcore_response.demand_code_rd.l3_hit_e.snoop_miss", "DEMAND_CODE_RD & L3_HIT_E & SNOOP_MISS"},
    {"offcore_response.demand_code_rd.l3_hit_e.snoop_none", "DEMAND_CODE_RD & L3_HIT_E & SNOOP_NONE"},
    {"offcore_response.demand_code_rd.l3_hit_e.snoop_not_needed", "DEMAND_CODE_RD & L3_HIT_E & SNOOP_NOT_NEEDED"},
    {"offcore_response.demand_code_rd.l3_hit_e.spl_hit", "DEMAND_CODE_RD & L3_HIT_E & SPL_HIT"},
    {"offcore_response.demand_code_rd.l3_hit_m.any_snoop", "DEMAND_CODE_RD & L3_HIT_M & ANY_SNOOP"},
    {"offcore_response.demand_code_rd.l3_hit_m.snoop_hit_no_fwd", "DEMAND_CODE_RD & L3_HIT_M & SNOOP_HIT_NO_FWD"},
    {"offcore_response.demand_code_rd.l3_hit_m.snoop_hitm", "DEMAND_CODE_RD & L3_HIT_M & SNOOP_HITM"},
    {"offcore_response.demand_code_rd.l3_hit_m.snoop_miss", "DEMAND_CODE_RD & L3_HIT_M & SNOOP_MISS"},
    {"offcore_response.demand_code_rd.l3_hit_m.snoop_none", "DEMAND_CODE_RD & L3_HIT_M & SNOOP_NONE"},
    {"offcore_response.demand_code_rd.l3_hit_m.snoop_not_needed", "DEMAND_CODE_RD & L3_HIT_M & SNOOP_NOT_NEEDED"},
    {"offcore_response.demand_code_rd.l3_hit_m.spl_hit", "DEMAND_CODE_RD & L3_HIT_M & SPL_HIT"},
    {"offcore_response.demand_code_rd.l3_hit_s.any_snoop", "DEMAND_CODE_RD & L3_HIT_S & ANY_SNOOP"},
    {"offcore_response.demand_code_rd.l3_hit_s.snoop_hit_no_fwd", "DEMAND_CODE_RD & L3_HIT_S & SNOOP_HIT_NO_FWD"},
    {"offcore_response.demand_code_rd.l3_hit_s.snoop_hitm", "DEMAND_CODE_RD & L3_HIT_S & SNOOP_HITM"},
    {"offcore_response.demand_code_rd.l3_hit_s.snoop_miss", "DEMAND_CODE_RD & L3_HIT_S & SNOOP_MISS"},
    {"offcore_response.demand_code_rd.l3_hit_s.snoop_none", "DEMAND_CODE_RD & L3_HIT_S & SNOOP_NONE"},
    {"offcore_response.demand_code_rd.l3_hit_s.snoop_not_needed", "DEMAND_CODE_RD & L3_HIT_S & SNOOP_NOT_NEEDED"},
    {"offcore_response.demand_code_rd.l3_hit_s.spl_hit", "DEMAND_CODE_RD & L3_HIT_S & SPL_HIT"},
    {"offcore_response.demand_code_rd.l4_hit_local_l4.any_snoop", "DEMAND_CODE_RD & L4_HIT_LOCAL_L4 & ANY_SNOOP"},
    {"offcore_response.demand_code_rd.l4_hit_local_l4.snoop_hit_no_fwd", "DEMAND_CODE_RD & L4_HIT_LOCAL_L4 & SNOOP_HIT_NO_FWD"},
    {"offcore_response.demand_code_rd.l4_hit_local_l4.snoop_hitm", "DEMAND_CODE_RD & L4_HIT_LOCAL_L4 & SNOOP_HITM"},
    {"offcore_response.demand_code_rd.l4_hit_local_l4.snoop_miss", "DEMAND_CODE_RD & L4_HIT_LOCAL_L4 & SNOOP_MISS"},
    {"offcore_response.demand_code_rd.l4_hit_local_l4.snoop_none", "DEMAND_CODE_RD & L4_HIT_LOCAL_L4 & SNOOP_NONE"},
    {"offcore_response.demand_code_rd.l4_hit_local_l4.snoop_not_needed", "DEMAND_CODE_RD & L4_HIT_LOCAL_L4 & SNOOP_NOT_NEEDED"},
    {"offcore_response.demand_code_rd.l4_hit_local_l4.spl_hit", "DEMAND_CODE_RD & L4_HIT_LOCAL_L4 & SPL_HIT"},
    {"offcore_response.demand_code_rd.supplier_none.any_snoop", "DEMAND_CODE_RD & SUPPLIER_NONE & ANY_SNOOP"},
    {"offcore_response.demand_code_rd.supplier_none.snoop_hit_no_fwd", "DEMAND_CODE_RD & SUPPLIER_NONE & SNOOP_HIT_NO_FWD"},
    {"offcore_response.demand_code_rd.supplier_none.snoop_hitm", "DEMAND_CODE_RD & SUPPLIER_NONE & SNOOP_HITM"},
    {"offcore_response.demand_code_rd.supplier_none.snoop_miss", "DEMAND_CODE_RD & SUPPLIER_NONE & SNOOP_MISS"},
    {"offcore_response.demand_code_rd.supplier_none.snoop_none", "DEMAND_CODE_RD & SUPPLIER_NONE & SNOOP_NONE"},
    {"offcore_response.demand_code_rd.supplier_none.snoop_not_needed", "DEMAND_CODE_RD & SUPPLIER_NONE & SNOOP_NOT_NEEDED"},
    {"offcore_response.demand_code_rd.supplier_none.spl_hit", "DEMAND_CODE_RD & SUPPLIER_NONE & SPL_HIT"},
    {"offcore_response.demand_data_rd.any_response", "Counts demand data reads that have any response type"},
    {"offcore_response.demand_data_rd.l3_hit.any_snoop", "DEMAND_DATA_RD & L3_HIT & ANY_SNOOP"},
    {"offcore_response.demand_data_rd.l3_hit.snoop_hit_no_fwd", "Counts demand data reads that hit in the L3 and the snoops to sibling cores hit in either E/S state and the line is not forwarded"},
    {"offcore_response.demand_data_rd.l3_hit.snoop_hitm", "DEMAND_DATA_RD & L3_HIT & SNOOP_HITM"},
    {"offcore_response.demand_data_rd.l3_hit.snoop_miss", "Counts demand data reads that hit in the L3 and the snoops sent to sibling cores return clean response"},
    {"offcore_response.demand_data_rd.l3_hit.snoop_none", "DEMAND_DATA_RD & L3_HIT & SNOOP_NONE"},
    {"offcore_response.demand_data_rd.l3_hit.snoop_not_needed", "Counts demand data reads that hit in the L3 and sibling core snoops are not needed as either the core-valid bit is not set or the shared line is present in multiple cores"},
    {"offcore_response.demand_data_rd.l3_hit.spl_hit", "DEMAND_DATA_RD & L3_HIT & SPL_HIT"},
    {"offcore_response.demand_data_rd.l3_hit_e.any_snoop", "DEMAND_DATA_RD & L3_HIT_E & ANY_SNOOP"},
    {"offcore_response.demand_data_rd.l3_hit_e.snoop_hit_no_fwd", "DEMAND_DATA_RD & L3_HIT_E & SNOOP_HIT_NO_FWD"},
    {"offcore_response.demand_data_rd.l3_hit_e.snoop_hitm", "DEMAND_DATA_RD & L3_HIT_E & SNOOP_HITM"},
    {"offcore_response.demand_data_rd.l3_hit_e.snoop_miss", "DEMAND_DATA_RD & L3_HIT_E & SNOOP_MISS"},
    {"offcore_response.demand_data_rd.l3_hit_e.snoop_none", "DEMAND_DATA_RD & L3_HIT_E & SNOOP_NONE"},
    {"offcore_response.demand_data_rd.l3_hit_e.snoop_not_needed", "DEMAND_DATA_RD & L3_HIT_E & SNOOP_NOT_NEEDED"},
    {"offcore_response.demand_data_rd.l3_hit_e.spl_hit", "DEMAND_DATA_RD & L3_HIT_E & SPL_HIT"},
    {"offcore_response.demand_data_rd.l3_hit_m.any_snoop", "DEMAND_DATA_RD & L3_HIT_M & ANY_SNOOP"},
    {"offcore_response.demand_data_rd.l3_hit_m.snoop_hit_no_fwd", "DEMAND_DATA_RD & L3_HIT_M & SNOOP_HIT_NO_FWD"},
    {"offcore_response.demand_data_rd.l3_hit_m.snoop_hitm", "DEMAND_DATA_RD & L3_HIT_M & SNOOP_HITM"},
    {"offcore_response.demand_data_rd.l3_hit_m.snoop_miss", "DEMAND_DATA_RD & L3_HIT_M & SNOOP_MISS"},
    {"offcore_response.demand_data_rd.l3_hit_m.snoop_none", "DEMAND_DATA_RD & L3_HIT_M & SNOOP_NONE"},
    {"offcore_response.demand_data_rd.l3_hit_m.snoop_not_needed", "DEMAND_DATA_RD & L3_HIT_M & SNOOP_NOT_NEEDED"},
    {"offcore_response.demand_data_rd.l3_hit_m.spl_hit", "DEMAND_DATA_RD & L3_HIT_M & SPL_HIT"},
    {"offcore_response.demand_data_rd.l3_hit_s.any_snoop", "DEMAND_DATA_RD & L3_HIT_S & ANY_SNOOP"},
    {"offcore_response.demand_data_rd.l3_hit_s.snoop_hit_no_fwd", "DEMAND_DATA_RD & L3_HIT_S & SNOOP_HIT_NO_FWD"},
    {"offcore_response.demand_data_rd.l3_hit_s.snoop_hitm", "DEMAND_DATA_RD & L3_HIT_S & SNOOP_HITM"},
    {"offcore_response.demand_data_rd.l3_hit_s.snoop_miss", "DEMAND_DATA_RD & L3_HIT_S & SNOOP_MISS"},
    {"offcore_response.demand_data_rd.l3_hit_s.snoop_none", "DEMAND_DATA_RD & L3_HIT_S & SNOOP_NONE"},
    {"offcore_response.demand_data_rd.l3_hit_s.snoop_not_needed", "DEMAND_DATA_RD & L3_HIT_S & SNOOP_NOT_NEEDED"},
    {"offcore_response.demand_data_rd.l3_hit_s.spl_hit", "DEMAND_DATA_RD & L3_HIT_S & SPL_HIT"},
    {"offcore_response.demand_data_rd.l4_hit_local_l4.any_snoop", "DEMAND_DATA_RD & L4_HIT_LOCAL_L4 & ANY_SNOOP"},
    {"offcore_response.demand_data_rd.l4_hit_local_l4.snoop_hit_no_fwd", "DEMAND_DATA_RD & L4_HIT_LOCAL_L4 & SNOOP_HIT_NO_FWD"},
    {"offcore_response.demand_data_rd.l4_hit_local_l4.snoop_hitm", "DEMAND_DATA_RD & L4_HIT_LOCAL_L4 & SNOOP_HITM"},
    {"offcore_response.demand_data_rd.l4_hit_local_l4.snoop_miss", "DEMAND_DATA_RD & L4_HIT_LOCAL_L4 & SNOOP_MISS"},
    {"offcore_response.demand_data_rd.l4_hit_local_l4.snoop_none", "DEMAND_DATA_RD & L4_HIT_LOCAL_L4 & SNOOP_NONE"},
    {"offcore_response.demand_data_rd.l4_hit_local_l4.snoop_not_needed", "DEMAND_DATA_RD & L4_HIT_LOCAL_L4 & SNOOP_NOT_NEEDED"},
    {"offcore_response.demand_data_rd.l4_hit_local_l4.spl_hit", "DEMAND_DATA_RD & L4_HIT_LOCAL_L4 & SPL_HIT"},
    {"offcore_response.demand_data_rd.supplier_none.any_snoop", "DEMAND_DATA_RD & SUPPLIER_NONE & ANY_SNOOP"},
    {"offcore_response.demand_data_rd.supplier_none.snoop_hit_no_fwd", "DEMAND_DATA_RD & SUPPLIER_NONE & SNOOP_HIT_NO_FWD"},
    {"offcore_response.demand_data_rd.supplier_none.snoop_hitm", "DEMAND_DATA_RD & SUPPLIER_NONE & SNOOP_HITM"},
    {"offcore_response.demand_data_rd.supplier_none.snoop_miss", "DEMAND_DATA_RD & SUPPLIER_NONE & SNOOP_MISS"},
    {"offcore_response.demand_data_rd.supplier_none.snoop_none", "DEMAND_DATA_RD & SUPPLIER_NONE & SNOOP_NONE"},
    {"offcore_response.demand_data_rd.supplier_none.snoop_not_needed", "DEMAND_DATA_RD & SUPPLIER_NONE & SNOOP_NOT_NEEDED"},
    {"offcore_response.demand_data_rd.supplier_none.spl_hit", "DEMAND_DATA_RD & SUPPLIER_NONE & SPL_HIT"},
    {"offcore_response.demand_rfo.any_response", "Counts all demand data writes (RFOs) that have any response type"},
    {"offcore_response.demand_rfo.l3_hit.any_snoop", "DEMAND_RFO & L3_HIT & ANY_SNOOP"},
    {"offcore_response.demand_rfo.l3_hit.snoop_hit_no_fwd", "Counts all demand data writes (RFOs) that hit in the L3 and the snoops to sibling cores hit in either E/S state and the line is not forwarded"},
    {"offcore_response.demand_rfo.l3_hit.snoop_hitm", "DEMAND_RFO & L3_HIT & SNOOP_HITM"},
    {"offcore_response.demand_rfo.l3_hit.snoop_miss", "Counts all demand data writes (RFOs) that hit in the L3 and the snoops sent to sibling cores return clean response"},
    {"offcore_response.demand_rfo.l3_hit.snoop_none", "DEMAND_RFO & L3_HIT & SNOOP_NONE"},
    {"offcore_response.demand_rfo.l3_hit.snoop_not_needed", "Counts all demand data writes (RFOs) that hit in the L3 and sibling core snoops are not needed as either the core-valid bit is not set or the shared line is present in multiple cores"},
    {"offcore_response.demand_rfo.l3_hit.spl_hit", "DEMAND_RFO & L3_HIT & SPL_HIT"},
    {"offcore_response.demand_rfo.l3_hit_e.any_snoop", "DEMAND_RFO & L3_HIT_E & ANY_SNOOP"},
    {"offcore_response.demand_rfo.l3_hit_e.snoop_hit_no_fwd", "DEMAND_RFO & L3_HIT_E & SNOOP_HIT_NO_FWD"},
    {"offcore_response.demand_rfo.l3_hit_e.snoop_hitm", "DEMAND_RFO & L3_HIT_E & SNOOP_HITM"},
    {"offcore_response.demand_rfo.l3_hit_e.snoop_miss", "DEMAND_RFO & L3_HIT_E & SNOOP_MISS"},
    {"offcore_response.demand_rfo.l3_hit_e.snoop_none", "DEMAND_RFO & L3_HIT_E & SNOOP_NONE"},
    {"offcore_response.demand_rfo.l3_hit_e.snoop_not_needed", "DEMAND_RFO & L3_HIT_E & SNOOP_NOT_NEEDED"},
    {"offcore_response.demand_rfo.l3_hit_e.spl_hit", "DEMAND_RFO & L3_HIT_E & SPL_HIT"},
    {"offcore_response.demand_rfo.l3_hit_m.any_snoop", "DEMAND_RFO & L3_HIT_M & ANY_SNOOP"},
    {"offcore_response.demand_rfo.l3_hit_m.snoop_hit_no_fwd", "DEMAND_RFO & L3_HIT_M & SNOOP_HIT_NO_FWD"},
    {"offcore_response.demand_rfo.l3_hit_m.snoop_hitm", "DEMAND_RFO & L3_HIT_M & SNOOP_HITM"},
    {"offcore_response.demand_rfo.l3_hit_m.snoop_miss", "DEMAND_RFO & L3_HIT_M & SNOOP_MISS"},
    {"offcore_response.demand_rfo.l3_hit_m.snoop_none", "DEMAND_RFO & L3_HIT_M & SNOOP_NONE"},
    {"offcore_response.demand_rfo.l3_hit_m.snoop_not_needed", "DEMAND_RFO & L3_HIT_M & SNOOP_NOT_NEEDED"},
    {"offcore_response.demand_rfo.l3_hit_m.spl_hit", "DEMAND_RFO & L3_HIT_M & SPL_HIT"},
    {"offcore_response.demand_rfo.l3_hit_s.any_snoop", "DEMAND_RFO & L3_HIT_S & ANY_SNOOP"},
    {"offcore_response.demand_rfo.l3_hit_s.snoop_hit_no_fwd", "DEMAND_RFO & L3_HIT_S & SNOOP_HIT_NO_FWD"},
    {"offcore_response.demand_rfo.l3_hit_s.snoop_hitm", "DEMAND_RFO & L3_HIT_S & SNOOP_HITM"},
    {"offcore_response.demand_rfo.l3_hit_s.snoop_miss", "DEMAND_RFO & L3_HIT_S & SNOOP_MISS"},
    {"offcore_response.demand_rfo.l3_hit_s.snoop_none", "DEMAND_RFO & L3_HIT_S & SNOOP_NONE"},
    {"offcore_response.demand_rfo.l3_hit_s.snoop_not_needed", "DEMAND_RFO & L3_HIT_S & SNOOP_NOT_NEEDED"},
    {"offcore_response.demand_rfo.l3_hit_s.spl_hit", "DEMAND_RFO & L3_HIT_S & SPL_HIT"},
    {"offcore_response.demand_rfo.l4_hit_local_l4.any_snoop", "DEMAND_RFO & L4_HIT_LOCAL_L4 & ANY_SNOOP"},
    {"offcore_response.demand_rfo.l4_hit_local_l4.snoop_hit_no_fwd", "DEMAND_RFO & L4_HIT_LOCAL_L4 & SNOOP_HIT_NO_FWD"},
    {"offcore_response.demand_rfo.l4_hit_local_l4.snoop_hitm", "DEMAND_RFO & L4_HIT_LOCAL_L4 & SNOOP_HITM"},
    {"offcore_response.demand_rfo.l4_hit_local_l4.snoop_miss", "DEMAND_RFO & L4_HIT_LOCAL_L4 & SNOOP_MISS"},
    {"offcore_response.demand_rfo.l4_hit_local_l4.snoop_none", "DEMAND_RFO & L4_HIT_LOCAL_L4 & SNOOP_NONE"},
    {"offcore_response.demand_rfo.l4_hit_local_l4.snoop_not_needed", "DEMAND_RFO & L4_HIT_LOCAL_L4 & SNOOP_NOT_NEEDED"},
    {"offcore_response.demand_rfo.l4_hit_local_l4.spl_hit", "DEMAND_RFO & L4_HIT_LOCAL_L4 & SPL_HIT"},
    {"offcore_response.demand_rfo.supplier_none.any_snoop", "DEMAND_RFO & SUPPLIER_NONE & ANY_SNOOP"},
    {"offcore_response.demand_rfo.supplier_none.snoop_hit_no_fwd", "DEMAND_RFO & SUPPLIER_NONE & SNOOP_HIT_NO_FWD"},
    {"offcore_response.demand_rfo.supplier_none.snoop_hitm", "DEMAND_RFO & SUPPLIER_NONE & SNOOP_HITM"},
    {"offcore_response.demand_rfo.supplier_none.snoop_miss", "DEMAND_RFO & SUPPLIER_NONE & SNOOP_MISS"},
    {"offcore_response.demand_rfo.supplier_none.snoop_none", "DEMAND_RFO & SUPPLIER_NONE & SNOOP_NONE"},
    {"offcore_response.demand_rfo.supplier_none.snoop_not_needed", "DEMAND_RFO & SUPPLIER_NONE & SNOOP_NOT_NEEDED"},
    {"offcore_response.demand_rfo.supplier_none.spl_hit", "DEMAND_RFO & SUPPLIER_NONE & SPL_HIT"},
    {"offcore_response.other.any_response", "Counts any other requests that have any response type"},
    {"offcore_response.other.l3_hit.any_snoop", "OTHER & L3_HIT & ANY_SNOOP"},
    {"offcore_response.other.l3_hit.snoop_hit_no_fwd", "Counts any other requests that hit in the L3 and the snoops to sibling cores hit in either E/S state and the line is not forwarded"},
    {"offcore_response.other.l3_hit.snoop_hitm", "OTHER & L3_HIT & SNOOP_HITM"},
    {"offcore_response.other.l3_hit.snoop_miss", "Counts any other requests that hit in the L3 and the snoops sent to sibling cores return clean response"},
    {"offcore_response.other.l3_hit.snoop_none", "OTHER & L3_HIT & SNOOP_NONE"},
    {"offcore_response.other.l3_hit.snoop_not_needed", "Counts any other requests that hit in the L3 and sibling core snoops are not needed as either the core-valid bit is not set or the shared line is present in multiple cores"},
    {"offcore_response.other.l3_hit.spl_hit", "OTHER & L3_HIT & SPL_HIT"},
    {"offcore_response.other.l3_hit_e.any_snoop", "OTHER & L3_HIT_E & ANY_SNOOP"},
    {"offcore_response.other.l3_hit_e.snoop_hit_no_fwd", "OTHER & L3_HIT_E & SNOOP_HIT_NO_FWD"},
    {"offcore_response.other.l3_hit_e.snoop_hitm", "OTHER & L3_HIT_E & SNOOP_HITM"},
    {"offcore_response.other.l3_hit_e.snoop_miss", "OTHER & L3_HIT_E & SNOOP_MISS"},
    {"offcore_response.other.l3_hit_e.snoop_none", "OTHER & L3_HIT_E & SNOOP_NONE"},
    {"offcore_response.other.l3_hit_e.snoop_not_needed", "OTHER & L3_HIT_E & SNOOP_NOT_NEEDED"},
    {"offcore_response.other.l3_hit_e.spl_hit", "OTHER & L3_HIT_E & SPL_HIT"},
    {"offcore_response.other.l3_hit_m.any_snoop", "OTHER & L3_HIT_M & ANY_SNOOP"},
    {"offcore_response.other.l3_hit_m.snoop_hit_no_fwd", "OTHER & L3_HIT_M & SNOOP_HIT_NO_FWD"},
    {"offcore_response.other.l3_hit_m.snoop_hitm", "OTHER & L3_HIT_M & SNOOP_HITM"},
    {"offcore_response.other.l3_hit_m.snoop_miss", "OTHER & L3_HIT_M & SNOOP_MISS"},
    {"offcore_response.other.l3_hit_m.snoop_none", "OTHER & L3_HIT_M & SNOOP_NONE"},
    {"offcore_response.other.l3_hit_m.snoop_not_needed", "OTHER & L3_HIT_M & SNOOP_NOT_NEEDED"},
    {"offcore_response.other.l3_hit_m.spl_hit", "OTHER & L3_HIT_M & SPL_HIT"},
    {"offcore_response.other.l3_hit_s.any_snoop", "OTHER & L3_HIT_S & ANY_SNOOP"},
    {"offcore_response.other.l3_hit_s.snoop_hit_no_fwd", "OTHER & L3_HIT_S & SNOOP_HIT_NO_FWD"},
    {"offcore_response.other.l3_hit_s.snoop_hitm", "OTHER & L3_HIT_S & SNOOP_HITM"},
    {"offcore_response.other.l3_hit_s.snoop_miss", "OTHER & L3_HIT_S & SNOOP_MISS"},
    {"offcore_response.other.l3_hit_s.snoop_none", "OTHER & L3_HIT_S & SNOOP_NONE"},
    {"offcore_response.other.l3_hit_s.snoop_not_needed", "OTHER & L3_HIT_S & SNOOP_NOT_NEEDED"},
    {"offcore_response.other.l3_hit_s.spl_hit", "OTHER & L3_HIT_S & SPL_HIT"},
    {"offcore_response.other.l4_hit_local_l4.any_snoop", "OTHER & L4_HIT_LOCAL_L4 & ANY_SNOOP"},
    {"offcore_response.other.l4_hit_local_l4.snoop_hit_no_fwd", "OTHER & L4_HIT_LOCAL_L4 & SNOOP_HIT_NO_FWD"},
    {"offcore_response.other.l4_hit_local_l4.snoop_hitm", "OTHER & L4_HIT_LOCAL_L4 & SNOOP_HITM"},
    {"offcore_response.other.l4_hit_local_l4.snoop_miss", "OTHER & L4_HIT_LOCAL_L4 & SNOOP_MISS"},
    {"offcore_response.other.l4_hit_local_l4.snoop_none", "OTHER & L4_HIT_LOCAL_L4 & SNOOP_NONE"},
    {"offcore_response.other.l4_hit_local_l4.snoop_not_needed", "OTHER & L4_HIT_LOCAL_L4 & SNOOP_NOT_NEEDED"},
    {"offcore_response.other.l4_hit_local_l4.spl_hit", "OTHER & L4_HIT_LOCAL_L4 & SPL_HIT"},
    {"offcore_response.other.supplier_none.any_snoop", "OTHER & SUPPLIER_NONE & ANY_SNOOP"},
    {"offcore_response.other.supplier_none.snoop_hit_no_fwd", "OTHER & SUPPLIER_NONE & SNOOP_HIT_NO_FWD"},
    {"offcore_response.other.supplier_none.snoop_hitm", "OTHER & SUPPLIER_NONE & SNOOP_HITM"},
    {"offcore_response.other.supplier_none.snoop_miss", "OTHER & SUPPLIER_NONE & SNOOP_MISS"},
    {"offcore_response.other.supplier_none.snoop_none", "OTHER & SUPPLIER_NONE & SNOOP_NONE"},
    {"offcore_response.other.supplier_none.snoop_not_needed", "OTHER & SUPPLIER_NONE & SNOOP_NOT_NEEDED"},
    {"offcore_response.other.supplier_none.spl_hit", "OTHER & SUPPLIER_NONE & SPL_HIT"},
    {"offcore_response.pf_l3_data_rd.any_response", "Counts all prefetch (that bring data to LLC only) data reads that have any response type"},
    {"offcore_response.pf_l3_data_rd.l3_hit.any_snoop", "PF_L3_DATA_RD & L3_HIT & ANY_SNOOP"},
    {"offcore_response.pf_l3_data_rd.l3_hit.snoop_hit_no_fwd", "Counts all prefetch (that bring data to LLC only) data reads that hit in the L3 and the snoops to sibling cores hit in either E/S state and the line is not forwarded"},
    {"offcore_response.pf_l3_data_rd.l3_hit.snoop_hitm", "PF_L3_DATA_RD & L3_HIT & SNOOP_HITM"},
    {"offcore_response.pf_l3_data_rd.l3_hit.snoop_miss", "Counts all prefetch (that bring data to LLC only) data reads that hit in the L3 and the snoops sent to sibling cores return clean response"},
    {"offcore_response.pf_l3_data_rd.l3_hit.snoop_none", "PF_L3_DATA_RD & L3_HIT & SNOOP_NONE"},
    {"offcore_response.pf_l3_data_rd.l3_hit.snoop_not_needed", "Counts all prefetch (that bring data to LLC only) data reads that hit in the L3 and sibling core snoops are not needed as either the core-valid bit is not set or the shared line is present in multiple cores"},
    {"offcore_response.pf_l3_data_rd.l3_hit.spl_hit", "PF_L3_DATA_RD & L3_HIT & SPL_HIT"},
    {"offcore_response.pf_l3_data_rd.l3_hit_e.any_snoop", "PF_L3_DATA_RD & L3_HIT_E & ANY_SNOOP"},
    {"offcore_response.pf_l3_data_rd.l3_hit_e.snoop_hit_no_fwd", "PF_L3_DATA_RD & L3_HIT_E & SNOOP_HIT_NO_FWD"},
    {"offcore_response.pf_l3_data_rd.l3_hit_e.snoop_hitm", "PF_L3_DATA_RD & L3_HIT_E & SNOOP_HITM"},
    {"offcore_response.pf_l3_data_rd.l3_hit_e.snoop_miss", "PF_L3_DATA_RD & L3_HIT_E & SNOOP_MISS"},
    {"offcore_response.pf_l3_data_rd.l3_hit_e.snoop_none", "PF_L3_DATA_RD & L3_HIT_E & SNOOP_NONE"},
    {"offcore_response.pf_l3_data_rd.l3_hit_e.snoop_not_needed", "PF_L3_DATA_RD & L3_HIT_E & SNOOP_NOT_NEEDED"},
    {"offcore_response.pf_l3_data_rd.l3_hit_e.spl_hit", "PF_L3_DATA_RD & L3_HIT_E & SPL_HIT"},
    {"offcore_response.pf_l3_data_rd.l3_hit_m.any_snoop", "PF_L3_DATA_RD & L3_HIT_M & ANY_SNOOP"},
    {"offcore_response.pf_l3_data_rd.l3_hit_m.snoop_hit_no_fwd", "PF_L3_DATA_RD & L3_HIT_M & SNOOP_HIT_NO_FWD"},
    {"offcore_response.pf_l3_data_rd.l3_hit_m.snoop_hitm", "PF_L3_DATA_RD & L3_HIT_M & SNOOP_HITM"},
    {"offcore_response.pf_l3_data_rd.l3_hit_m.snoop_miss", "PF_L3_DATA_RD & L3_HIT_M & SNOOP_MISS"},
    {"offcore_response.pf_l3_data_rd.l3_hit_m.snoop_none", "PF_L3_DATA_RD & L3_HIT_M & SNOOP_NONE"},
    {"offcore_response.pf_l3_data_rd.l3_hit_m.snoop_not_needed", "PF_L3_DATA_RD & L3_HIT_M & SNOOP_NOT_NEEDED"},
    {"offcore_response.pf_l3_data_rd.l3_hit_m.spl_hit", "PF_L3_DATA_RD & L3_HIT_M & SPL_HIT"},
    {"offcore_response.pf_l3_data_rd.l3_hit_s.any_snoop", "PF_L3_DATA_RD & L3_HIT_S & ANY_SNOOP"},
    {"offcore_response.pf_l3_data_rd.l3_hit_s.snoop_hit_no_fwd", "PF_L3_DATA_RD & L3_HIT_S & SNOOP_HIT_NO_FWD"},
    {"offcore_response.pf_l3_data_rd.l3_hit_s.snoop_hitm", "PF_L3_DATA_RD & L3_HIT_S & SNOOP_HITM"},
    {"offcore_response.pf_l3_data_rd.l3_hit_s.snoop_miss", "PF_L3_DATA_RD & L3_HIT_S & SNOOP_MISS"},
    {"offcore_response.pf_l3_data_rd.l3_hit_s.snoop_none", "PF_L3_DATA_RD & L3_HIT_S & SNOOP_NONE"},
    {"offcore_response.pf_l3_data_rd.l3_hit_s.snoop_not_needed", "PF_L3_DATA_RD & L3_HIT_S & SNOOP_NOT_NEEDED"},
    {"offcore_response.pf_l3_data_rd.l3_hit_s.spl_hit", "PF_L3_DATA_RD & L3_HIT_S & SPL_HIT"},
    {"offcore_response.pf_l3_data_rd.l4_hit_local_l4.any_snoop", "PF_L3_DATA_RD & L4_HIT_LOCAL_L4 & ANY_SNOOP"},
    {"offcore_response.pf_l3_data_rd.l4_hit_local_l4.snoop_hit_no_fwd", "PF_L3_DATA_RD & L4_HIT_LOCAL_L4 & SNOOP_HIT_NO_FWD"},
    {"offcore_response.pf_l3_data_rd.l4_hit_local_l4.snoop_hitm", "PF_L3_DATA_RD & L4_HIT_LOCAL_L4 & SNOOP_HITM"},
    {"offcore_response.pf_l3_data_rd.l4_hit_local_l4.snoop_miss", "PF_L3_DATA_RD & L4_HIT_LOCAL_L4 & SNOOP_MISS"},
    {"offcore_response.pf_l3_data_rd.l4_hit_local_l4.snoop_none", "PF_L3_DATA_RD & L4_HIT_LOCAL_L4 & SNOOP_NONE"},
    {"offcore_response.pf_l3_data_rd.l4_hit_local_l4.snoop_not_needed", "PF_L3_DATA_RD & L4_HIT_LOCAL_L4 & SNOOP_NOT_NEEDED"},
    {"offcore_response.pf_l3_data_rd.l4_hit_local_l4.spl_hit", "PF_L3_DATA_RD & L4_HIT_LOCAL_L4 & SPL_HIT"},
    {"offcore_response.pf_l3_data_rd.supplier_none.any_snoop", "PF_L3_DATA_RD & SUPPLIER_NONE & ANY_SNOOP"},
    {"offcore_response.pf_l3_data_rd.supplier_none.snoop_hit_no_fwd", "PF_L3_DATA_RD & SUPPLIER_NONE & SNOOP_HIT_NO_FWD"},
    {"offcore_response.pf_l3_data_rd.supplier_none.snoop_hitm", "PF_L3_DATA_RD & SUPPLIER_NONE & SNOOP_HITM"},
    {"offcore_response.pf_l3_data_rd.supplier_none.snoop_miss", "PF_L3_DATA_RD & SUPPLIER_NONE & SNOOP_MISS"},
    {"offcore_response.pf_l3_data_rd.supplier_none.snoop_none", "PF_L3_DATA_RD & SUPPLIER_NONE & SNOOP_NONE"},
    {"offcore_response.pf_l3_data_rd.supplier_none.snoop_not_needed", "PF_L3_DATA_RD & SUPPLIER_NONE & SNOOP_NOT_NEEDED"},
    {"offcore_response.pf_l3_data_rd.supplier_none.spl_hit", "PF_L3_DATA_RD & SUPPLIER_NONE & SPL_HIT"},
    {"offcore_response.pf_l3_rfo.any_response", "Counts all prefetch (that bring data to LLC only) RFOs that have any response type"},
    {"offcore_response.pf_l3_rfo.l3_hit.any_snoop", "PF_L3_RFO & L3_HIT & ANY_SNOOP"},
    {"offcore_response.pf_l3_rfo.l3_hit.snoop_hit_no_fwd", "Counts all prefetch (that bring data to LLC only) RFOs that hit in the L3 and the snoops to sibling cores hit in either E/S state and the line is not forwarded"},
    {"offcore_response.pf_l3_rfo.l3_hit.snoop_hitm", "PF_L3_RFO & L3_HIT & SNOOP_HITM"},
    {"offcore_response.pf_l3_rfo.l3_hit.snoop_miss", "Counts all prefetch (that bring data to LLC only) RFOs that hit in the L3 and the snoops sent to sibling cores return clean response"},
    {"offcore_response.pf_l3_rfo.l3_hit.snoop_none", "PF_L3_RFO & L3_HIT & SNOOP_NONE"},
    {"offcore_response.pf_l3_rfo.l3_hit.snoop_not_needed", "Counts all prefetch (that bring data to LLC only) RFOs that hit in the L3 and sibling core snoops are not needed as either the core-valid bit is not set or the shared line is present in multiple cores"},
    {"offcore_response.pf_l3_rfo.l3_hit.spl_hit", "PF_L3_RFO & L3_HIT & SPL_HIT"},
    {"offcore_response.pf_l3_rfo.l3_hit_e.any_snoop", "PF_L3_RFO & L3_HIT_E & ANY_SNOOP"},
    {"offcore_response.pf_l3_rfo.l3_hit_e.snoop_hit_no_fwd", "PF_L3_RFO & L3_HIT_E & SNOOP_HIT_NO_FWD"},
    {"offcore_response.pf_l3_rfo.l3_hit_e.snoop_hitm", "PF_L3_RFO & L3_HIT_E & SNOOP_HITM"},
    {"offcore_response.pf_l3_rfo.l3_hit_e.snoop_miss", "PF_L3_RFO & L3_HIT_E & SNOOP_MISS"},
    {"offcore_response.pf_l3_rfo.l3_hit_e.snoop_none", "PF_L3_RFO & L3_HIT_E & SNOOP_NONE"},
    {"offcore_response.pf_l3_rfo.l3_hit_e.snoop_not_needed", "PF_L3_RFO & L3_HIT_E & SNOOP_NOT_NEEDED"},
    {"offcore_response.pf_l3_rfo.l3_hit_e.spl_hit", "PF_L3_RFO & L3_HIT_E & SPL_HIT"},
    {"offcore_response.pf_l3_rfo.l3_hit_m.any_snoop", "PF_L3_RFO & L3_HIT_M & ANY_SNOOP"},
    {"offcore_response.pf_l3_rfo.l3_hit_m.snoop_hit_no_fwd", "PF_L3_RFO & L3_HIT_M & SNOOP_HIT_NO_FWD"},
    {"offcore_response.pf_l3_rfo.l3_hit_m.snoop_hitm", "PF_L3_RFO & L3_HIT_M & SNOOP_HITM"},
    {"offcore_response.pf_l3_rfo.l3_hit_m.snoop_miss", "PF_L3_RFO & L3_HIT_M & SNOOP_MISS"},
    {"offcore_response.pf_l3_rfo.l3_hit_m.snoop_none", "PF_L3_RFO & L3_HIT_M & SNOOP_NONE"},
    {"offcore_response.pf_l3_rfo.l3_hit_m.snoop_not_needed", "PF_L3_RFO & L3_HIT_M & SNOOP_NOT_NEEDED"},
    {"offcore_response.pf_l3_rfo.l3_hit_m.spl_hit", "PF_L3_RFO & L3_HIT_M & SPL_HIT"},
    {"offcore_response.pf_l3_rfo.l3_hit_s.any_snoop", "PF_L3_RFO & L3_HIT_S & ANY_SNOOP"},
    {"offcore_response.pf_l3_rfo.l3_hit_s.snoop_hit_no_fwd", "PF_L3_RFO & L3_HIT_S & SNOOP_HIT_NO_FWD"},
    {"offcore_response.pf_l3_rfo.l3_hit_s.snoop_hitm", "PF_L3_RFO & L3_HIT_S & SNOOP_HITM"},
    {"offcore_response.pf_l3_rfo.l3_hit_s.snoop_miss", "PF_L3_RFO & L3_HIT_S & SNOOP_MISS"},
    {"offcore_response.pf_l3_rfo.l3_hit_s.snoop_none", "PF_L3_RFO & L3_HIT_S & SNOOP_NONE"},
    {"offcore_response.pf_l3_rfo.l3_hit_s.snoop_not_needed", "PF_L3_RFO & L3_HIT_S & SNOOP_NOT_NEEDED"},
    {"offcore_response.pf_l3_rfo.l3_hit_s.spl_hit", "PF_L3_RFO & L3_HIT_S & SPL_HIT"},
    {"offcore_response.pf_l3_rfo.l4_hit_local_l4.any_snoop", "PF_L3_RFO & L4_HIT_LOCAL_L4 & ANY_SNOOP"},
    {"offcore_response.pf_l3_rfo.l4_hit_local_l4.snoop_hit_no_fwd", "PF_L3_RFO & L4_HIT_LOCAL_L4 & SNOOP_HIT_NO_FWD"},
    {"offcore_response.pf_l3_rfo.l4_hit_local_l4.snoop_hitm", "PF_L3_RFO & L4_HIT_LOCAL_L4 & SNOOP_HITM"},
    {"offcore_response.pf_l3_rfo.l4_hit_local_l4.snoop_miss", "PF_L3_RFO & L4_HIT_LOCAL_L4 & SNOOP_MISS"},
    {"offcore_response.pf_l3_rfo.l4_hit_local_l4.snoop_none", "PF_L3_RFO & L4_HIT_LOCAL_L4 & SNOOP_NONE"},
    {"offcore_response.pf_l3_rfo.l4_hit_local_l4.snoop_not_needed", "PF_L3_RFO & L4_HIT_LOCAL_L4 & SNOOP_NOT_NEEDED"},
    {"offcore_response.pf_l3_rfo.l4_hit_local_l4.spl_hit", "PF_L3_RFO & L4_HIT_LOCAL_L4 & SPL_HIT"},
    {"offcore_response.pf_l3_rfo.supplier_none.any_snoop", "PF_L3_RFO & SUPPLIER_NONE & ANY_SNOOP"},
    {"offcore_response.pf_l3_rfo.supplier_none.snoop_hit_no_fwd", "PF_L3_RFO & SUPPLIER_NONE & SNOOP_HIT_NO_FWD"},
    {"offcore_response.pf_l3_rfo.supplier_none.snoop_hitm", "PF_L3_RFO & SUPPLIER_NONE & SNOOP_HITM"},
    {"offcore_response.pf_l3_rfo.supplier_none.snoop_miss", "PF_L3_RFO & SUPPLIER_NONE & SNOOP_MISS"},
    {"offcore_response.pf_l3_rfo.supplier_none.snoop_none", "PF_L3_RFO & SUPPLIER_NONE & SNOOP_NONE"},
    {"offcore_response.pf_l3_rfo.supplier_none.snoop_not_needed", "PF_L3_RFO & SUPPLIER_NONE & SNOOP_NOT_NEEDED"},
    {"offcore_response.pf_l3_rfo.supplier_none.spl_hit", "PF_L3_RFO & SUPPLIER_NONE & SPL_HIT"},
    {"offcore_response.streaming_stores.any_response", "Counts streaming stores that have any response type"},
    {"offcore_response.streaming_stores.l3_hit.any_snoop", "STREAMING_STORES & L3_HIT & ANY_SNOOP"},
    {"offcore_response.streaming_stores.l3_hit.snoop_hit_no_fwd", "Counts streaming stores that hit in the L3 and the snoops to sibling cores hit in either E/S state and the line is not forwarded"},
    {"offcore_response.streaming_stores.l3_hit.snoop_hitm", "STREAMING_STORES & L3_HIT & SNOOP_HITM"},
    {"offcore_response.streaming_stores.l3_hit.snoop_miss", "Counts streaming stores that hit in the L3 and the snoops sent to sibling cores return clean response"},
    {"offcore_response.streaming_stores.l3_hit.snoop_none", "STREAMING_STORES & L3_HIT & SNOOP_NONE"},
    {"offcore_response.streaming_stores.l3_hit.snoop_not_needed", "Counts streaming stores that hit in the L3 and sibling core snoops are not needed as either the core-valid bit is not set or the shared line is present in multiple cores"},
    {"offcore_response.streaming_stores.l3_hit.spl_hit", "STREAMING_STORES & L3_HIT & SPL_HIT"},
    {"offcore_response.streaming_stores.l3_hit_e.any_snoop", "STREAMING_STORES & L3_HIT_E & ANY_SNOOP"},
    {"offcore_response.streaming_stores.l3_hit_e.snoop_hit_no_fwd", "STREAMING_STORES & L3_HIT_E & SNOOP_HIT_NO_FWD"},
    {"offcore_response.streaming_stores.l3_hit_e.snoop_hitm", "STREAMING_STORES & L3_HIT_E & SNOOP_HITM"},
    {"offcore_response.streaming_stores.l3_hit_e.snoop_miss", "STREAMING_STORES & L3_HIT_E & SNOOP_MISS"},
    {"offcore_response.streaming_stores.l3_hit_e.snoop_none", "STREAMING_STORES & L3_HIT_E & SNOOP_NONE"},
    {"offcore_response.streaming_stores.l3_hit_e.snoop_not_needed", "STREAMING_STORES & L3_HIT_E & SNOOP_NOT_NEEDED"},
    {"offcore_response.streaming_stores.l3_hit_e.spl_hit", "STREAMING_STORES & L3_HIT_E & SPL_HIT"},
    {"offcore_response.streaming_stores.l3_hit_m.any_snoop", "STREAMING_STORES & L3_HIT_M & ANY_SNOOP"},
    {"offcore_response.streaming_stores.l3_hit_m.snoop_hit_no_fwd", "STREAMING_STORES & L3_HIT_M & SNOOP_HIT_NO_FWD"},
    {"offcore_response.streaming_stores.l3_hit_m.snoop_hitm", "STREAMING_STORES & L3_HIT_M & SNOOP_HITM"},
    {"offcore_response.streaming_stores.l3_hit_m.snoop_miss", "STREAMING_STORES & L3_HIT_M & SNOOP_MISS"},
    {"offcore_response.streaming_stores.l3_hit_m.snoop_none", "STREAMING_STORES & L3_HIT_M & SNOOP_NONE"},
    {"offcore_response.streaming_stores.l3_hit_m.snoop_not_needed", "STREAMING_STORES & L3_HIT_M & SNOOP_NOT_NEEDED"},
    {"offcore_response.streaming_stores.l3_hit_m.spl_hit", "STREAMING_STORES & L3_HIT_M & SPL_HIT"},
    {"offcore_response.streaming_stores.l3_hit_s.any_snoop", "STREAMING_STORES & L3_HIT_S & ANY_SNOOP"},
    {"offcore_response.streaming_stores.l3_hit_s.snoop_hit_no_fwd", "STREAMING_STORES & L3_HIT_S & SNOOP_HIT_NO_FWD"},
    {"offcore_response.streaming_stores.l3_hit_s.snoop_hitm", "STREAMING_STORES & L3_HIT_S & SNOOP_HITM"},
    {"offcore_response.streaming_stores.l3_hit_s.snoop_miss", "STREAMING_STORES & L3_HIT_S & SNOOP_MISS"},
    {"offcore_response.streaming_stores.l3_hit_s.snoop_none", "STREAMING_STORES & L3_HIT_S & SNOOP_NONE"},
    {"offcore_response.streaming_stores.l3_hit_s.snoop_not_needed", "STREAMING_STORES & L3_HIT_S & SNOOP_NOT_NEEDED"},
    {"offcore_response.streaming_stores.l3_hit_s.spl_hit", "STREAMING_STORES & L3_HIT_S & SPL_HIT"},
    {"offcore_response.streaming_stores.l4_hit_local_l4.any_snoop", "STREAMING_STORES & L4_HIT_LOCAL_L4 & ANY_SNOOP"},
    {"offcore_response.streaming_stores.l4_hit_local_l4.snoop_hit_no_fwd", "STREAMING_STORES & L4_HIT_LOCAL_L4 & SNOOP_HIT_NO_FWD"},
    {"offcore_response.streaming_stores.l4_hit_local_l4.snoop_hitm", "STREAMING_STORES & L4_HIT_LOCAL_L4 & SNOOP_HITM"},
    {"offcore_response.streaming_stores.l4_hit_local_l4.snoop_miss", "STREAMING_STORES & L4_HIT_LOCAL_L4 & SNOOP_MISS"},
    {"offcore_response.streaming_stores.l4_hit_local_l4.snoop_none", "STREAMING_STORES & L4_HIT_LOCAL_L4 & SNOOP_NONE"},
    {"offcore_response.streaming_stores.l4_hit_local_l4.snoop_not_needed", "STREAMING_STORES & L4_HIT_LOCAL_L4 & SNOOP_NOT_NEEDED"},
    {"offcore_response.streaming_stores.l4_hit_local_l4.spl_hit", "STREAMING_STORES & L4_HIT_LOCAL_L4 & SPL_HIT"},
    {"offcore_response.streaming_stores.supplier_none.any_snoop", "STREAMING_STORES & SUPPLIER_NONE & ANY_SNOOP"},
    {"offcore_response.streaming_stores.supplier_none.snoop_hit_no_fwd", "STREAMING_STORES & SUPPLIER_NONE & SNOOP_HIT_NO_FWD"},
    {"offcore_response.streaming_stores.supplier_none.snoop_hitm", "STREAMING_STORES & SUPPLIER_NONE & SNOOP_HITM"},
    {"offcore_response.streaming_stores.supplier_none.snoop_miss", "STREAMING_STORES & SUPPLIER_NONE & SNOOP_MISS"},
    {"offcore_response.streaming_stores.supplier_none.snoop_none", "STREAMING_STORES & SUPPLIER_NONE & SNOOP_NONE"},
    {"offcore_response.streaming_stores.supplier_none.snoop_not_needed", "STREAMING_STORES & SUPPLIER_NONE & SNOOP_NOT_NEEDED"},
    {"offcore_response.streaming_stores.supplier_none.spl_hit", "STREAMING_STORES & SUPPLIER_NONE & SPL_HIT"},
    {"sq_misc.split_lock", "Number of cache line split locks sent to uncore"},
    {"fp_arith_inst_retired.128b_packed_double", "Number of SSE/AVX computational 128-bit packed double precision floating-point instructions retired. Each count represents 2 computations. Applies to SSE* and AVX* packed double precision floating-point instructions: ADD SUB MUL DIV MIN MAX SQRT DPP FM(N)ADD/SUB. DPP and FM(N)ADD/SUB instructions count twice as they perform multiple calculations per element"},
    {"fp_arith_inst_retired.128b_packed_single", "Number of SSE/AVX computational 128-bit packed single precision floating-point instructions retired. Each count represents 4 computations. Applies to SSE* and AVX* packed single precision floating-point instructions: ADD SUB MUL DIV MIN MAX RCP RSQRT SQRT DPP FM(N)ADD/SUB. DPP and FM(N)ADD/SUB instructions count twice as they perform multiple calculations per element"},
    {"fp_arith_inst_retired.256b_packed_double", "Number of SSE/AVX computational 256-bit packed double precision floating-point instructions retired. Each count represents 4 computations. Applies to SSE* and AVX* packed double precision floating-point instructions: ADD SUB MUL DIV MIN MAX SQRT DPP FM(N)ADD/SUB. DPP and FM(N)ADD/SUB instructions count twice as they perform multiple calculations per element"},
    {"fp_arith_inst_retired.256b_packed_single", "Number of SSE/AVX computational 256-bit packed single precision floating-point instructions retired. Each count represents 8 computations. Applies to SSE* and AVX* packed single precision floating-point instructions: ADD SUB MUL DIV MIN MAX RCP RSQRT SQRT DPP FM(N)ADD/SUB. DPP and FM(N)ADD/SUB instructions count twice as they perform multiple calculations per element"},
    {"fp_arith_inst_retired.scalar_double", "Number of SSE/AVX computational scalar double precision floating-point instructions retired. Each count represents 1 computation. Applies to SSE* and AVX* scalar double precision floating-point instructions: ADD SUB MUL DIV MIN MAX SQRT FM(N)ADD/SUB. FM(N)ADD/SUB instructions count twice as they perform multiple calculations per element"},
    {"fp_arith_inst_retired.scalar_single", "Number of SSE/AVX computational scalar single precision floating-point instructions retired. Each count represents 1 computation. Applies to SSE* and AVX* scalar single precision floating-point instructions: ADD SUB MUL DIV MIN MAX RCP RSQRT SQRT FM(N)ADD/SUB. FM(N)ADD/SUB instructions count twice as they perform multiple calculations per element"},
    {"fp_assist.any", "Cycles with any input/output SSE or FP assist"},
    {"dsb2mite_switches.penalty_cycles", "Decode Stream Buffer (DSB)-to-MITE switch true penalty cycles"},
    {"frontend_retired.dsb_miss", "Retired Instructions who experienced decode stream buffer (DSB - the decoded instruction-cache) miss (Precise event)"},
    {"frontend_retired.itlb_miss", "Retired Instructions who experienced iTLB true miss (Precise event)"},
    {"frontend_retired.l1i_miss", "Retired Instructions who experienced Instruction L1 Cache true miss (Precise event)"},
    {"frontend_retired.l2_miss", "Retired Instructions who experienced Instruction L2 Cache true miss (Precise event)"},
    {"frontend_retired.latency_ge_128", "Retired instructions that are fetched after an interval where the front-end delivered no uops for a period of 128 cycles which was not interrupted by a back-end stall (Precise event)"},
    {"frontend_retired.latency_ge_16", "Retired instructions that are fetched after an interval where the front-end delivered no uops for a period of 16 cycles which was not interrupted by a back-end stall (Precise event)"},
    {"frontend_retired.latency_ge_2", "Retired instructions that are fetched after an interval where the front-end delivered no uops for a period of 2 cycles which was not interrupted by a back-end stall (Precise event)"},
    {"frontend_retired.latency_ge_256", "Retired instructions that are fetched after an interval where the front-end delivered no uops for a period of 256 cycles which was not interrupted by a back-end stall (Precise event)"},
    {"frontend_retired.latency_ge_2_bubbles_ge_1", "Retired instructions that are fetched after an interval where the front-end had at least 1 bubble-slot for a period of 2 cycles which was not interrupted by a back-end stall (Precise event)"},
    {"frontend_retired.latency_ge_2_bubbles_ge_2", "Retired instructions that are fetched after an interval where the front-end had at least 2 bubble-slots for a period of 2 cycles which was not interrupted by a back-end stall (Precise event)"},
    {"frontend_retired.latency_ge_2_bubbles_ge_3", "Retired instructions that are fetched after an interval where the front-end had at least 3 bubble-slots for a period of 2 cycles which was not interrupted by a back-end stall (Precise event)"},
    {"frontend_retired.latency_ge_32", "Retired instructions that are fetched after an interval where the front-end delivered no uops for a period of 32 cycles which was not interrupted by a back-end stall (Precise event)"},
    {"frontend_retired.latency_ge_4", "Retired instructions that are fetched after an interval where the front-end delivered no uops for a period of 4 cycles which was not interrupted by a back-end stall (Precise event)"},
    {"frontend_retired.latency_ge_512", "Retired instructions that are fetched after an interval where the front-end delivered no uops for a period of 512 cycles which was not interrupted by a back-end stall (Precise event)"},
    {"frontend_retired.latency_ge_64", "Retired instructions that are fetched after an interval where the front-end delivered no uops for a period of 64 cycles which was not interrupted by a back-end stall (Precise event)"},
    {"frontend_retired.latency_ge_8", "Retired instructions that are fetched after an interval where the front-end delivered no uops for a period of 8 cycles which was not interrupted by a back-end stall (Precise event)"},
    {"frontend_retired.stlb_miss", "Retired Instructions who experienced STLB (2nd level TLB) true miss (Precise event)"},
    {"icache_16b.ifdata_stall", "Cycles where a code fetch is stalled due to L1 instruction cache miss"},
    {"icache_64b.iftag_hit", "Instruction fetch tag lookups that hit in the instruction cache (L1I). Counts at 64-byte cache-line granularity"},
    {"icache_64b.iftag_miss", "Instruction fetch tag lookups that miss in the instruction cache (L1I). Counts at 64-byte cache-line granularity"},
    {"icache_64b.iftag_stall", "Cycles where a code fetch is stalled due to L1 instruction cache tag miss"},
    {"idq.all_dsb_cycles_4_uops", "Cycles Decode Stream Buffer (DSB) is delivering 4 Uops"},
    {"idq.all_dsb_cycles_any_uops", "Cycles Decode Stream Buffer (DSB) is delivering any Uop"},
    {"idq.all_mite_cycles_4_uops", "Cycles MITE is delivering 4 Uops"},
    {"idq.all_mite_cycles_any_uops", "Cycles MITE is delivering any Uop"},
    {"idq.dsb_cycles", "Cycles when uops are being delivered to Instruction Decode Queue (IDQ) from Decode Stream Buffer (DSB) path"},
    {"idq.dsb_uops", "Uops delivered to Instruction Decode Queue (IDQ) from the Decode Stream Buffer (DSB) path"},
    {"idq.mite_cycles", "Cycles when uops are being delivered to Instruction Decode Queue (IDQ) from MITE path"},
    {"idq.mite_uops", "Uops delivered to Instruction Decode Queue (IDQ) from MITE path"},
    {"idq.ms_cycles", "Cycles when uops are being delivered to Instruction Decode Queue (IDQ) while Microcode Sequenser (MS) is busy"},
    {"idq.ms_dsb_cycles", "Cycles when uops initiated by Decode Stream Buffer (DSB) are being delivered to Instruction Decode Queue (IDQ) while Microcode Sequenser (MS) is busy"},
    {"idq.ms_mite_uops", "Uops initiated by MITE and delivered to Instruction Decode Queue (IDQ) while Microcode Sequenser (MS) is busy"},
    {"idq.ms_switches", "Number of switches from DSB (Decode Stream Buffer) or MITE (legacy decode pipeline) to the Microcode Sequencer"},
    {"idq.ms_uops", "Uops delivered to Instruction Decode Queue (IDQ) while Microcode Sequenser (MS) is busy"},
    {"idq_uops_not_delivered.core", "Uops not delivered to Resource Allocation Table (RAT) per thread when backend of the machine is not stalled"},
    {"idq_uops_not_delivered.cycles_0_uops_deliv.core", "Cycles per thread when 4 or more uops are not delivered to Resource Allocation Table (RAT) when backend of the machine is not stalled"},
    {"idq_uops_not_delivered.cycles_fe_was_ok", "Counts cycles FE delivered 4 uops or Resource Allocation Table (RAT) was stalling FE"},
    {"idq_uops_not_delivered.cycles_le_1_uop_deliv.core", "Cycles per thread when 3 or more uops are not delivered to Resource Allocation Table (RAT) when backend of the machine is not stalled"},
    {"idq_uops_not_delivered.cycles_le_2_uop_deliv.core", "Cycles with less than 2 uops delivered by the front end"},
    {"idq_uops_not_delivered.cycles_le_3_uop_deliv.core", "Cycles with less than 3 uops delivered by the front end"},
    {"cycle_activity.cycles_l3_miss", "Cycles while L3 cache miss demand load is outstanding"},
    {"cycle_activity.stalls_l3_miss", "Execution stalls while L3 cache miss demand load is outstanding"},
    {"hle_retired.aborted", "Number of times an HLE execution aborted due to any reasons (multiple categories may count as one) (Precise event)"},
    {"hle_retired.aborted_events", "Number of times an HLE execution aborted due to unfriendly events (such as interrupts)"},
    {"hle_retired.aborted_mem", "Number of times an HLE execution aborted due to various memory events (e.g., read/write capacity and conflicts)"},
    {"hle_retired.aborted_memtype", "Number of times an HLE execution aborted due to incompatible memory type"},
    {"hle_retired.aborted_timer", "Number of times an HLE execution aborted due to hardware timer expiration"},
    {"hle_retired.aborted_unfriendly", "Number of times an HLE execution aborted due to HLE-unfriendly instructions and certain unfriendly events (such as AD assists etc.)"},
    {"hle_retired.commit", "Number of times an HLE execution successfully committed"},
    {"hle_retired.start", "Number of times an HLE execution started"},
    {"machine_clears.memory_ordering", "Counts the number of machine clears due to memory order conflicts Spec update: SKL089"},
    {"mem_trans_retired.load_latency_gt_128", "Counts loads when the latency from first dispatch to completion is greater than 128 cycles (Must be precise)"},
    {"mem_trans_retired.load_latency_gt_16", "Counts loads when the latency from first dispatch to completion is greater than 16 cycles (Must be precise)"},
    {"mem_trans_retired.load_latency_gt_256", "Counts loads when the latency from first dispatch to completion is greater than 256 cycles (Must be precise)"},
    {"mem_trans_retired.load_latency_gt_32", "Counts loads when the latency from first dispatch to completion is greater than 32 cycles (Must be precise)"},
    {"mem_trans_retired.load_latency_gt_4", "Counts loads when the latency from first dispatch to completion is greater than 4 cycles (Must be precise)"},
    {"mem_trans_retired.load_latency_gt_512", "Counts loads when the latency from first dispatch to completion is greater than 512 cycles (Must be precise)"},
    {"mem_trans_retired.load_latency_gt_64", "Counts loads when the latency from first dispatch to completion is greater than 64 cycles (Must be precise)"},
    {"mem_trans_retired.load_latency_gt_8", "Counts loads when the latency from first dispatch to completion is greater than 8 cycles (Must be precise)"},
    {"offcore_requests.l3_miss_demand_data_rd", "Demand Data Read requests who miss L3 cache"},
    {"offcore_requests_outstanding.cycles_with_l3_miss_demand_data_rd", "Cycles with at least 1 Demand Data Read requests who miss L3 cache in the superQ"},
    {"offcore_requests_outstanding.l3_miss_demand_data_rd", "Counts number of Offcore outstanding Demand Data Read requests that miss L3 cache in the superQ every cycle"},
    {"offcore_requests_outstanding.l3_miss_demand_data_rd_ge_6", "Cycles with at least 6 Demand Data Read requests that miss L3 cache in the superQ"},
    {"offcore_response.demand_code_rd.l3_hit.snoop_non_dram", "DEMAND_CODE_RD & L3_HIT & SNOOP_NON_DRAM"},
    {"offcore_response.demand_code_rd.l3_hit_e.snoop_non_dram", "DEMAND_CODE_RD & L3_HIT_E & SNOOP_NON_DRAM"},
    {"offcore_response.demand_code_rd.l3_hit_m.snoop_non_dram", "DEMAND_CODE_RD & L3_HIT_M & SNOOP_NON_DRAM"},
    {"offcore_response.demand_code_rd.l3_hit_s.snoop_non_dram", "DEMAND_CODE_RD & L3_HIT_S & SNOOP_NON_DRAM"},
    {"offcore_response.demand_code_rd.l3_miss.any_snoop", "DEMAND_CODE_RD & L3_MISS & ANY_SNOOP"},
    {"offcore_response.demand_code_rd.l3_miss.snoop_hit_no_fwd", "DEMAND_CODE_RD & L3_MISS & SNOOP_HIT_NO_FWD"},
    {"offcore_response.demand_code_rd.l3_miss.snoop_hitm", "DEMAND_CODE_RD & L3_MISS & SNOOP_HITM"},
    {"offcore_response.demand_code_rd.l3_miss.snoop_miss", "DEMAND_CODE_RD & L3_MISS & SNOOP_MISS"},
    {"offcore_response.demand_code_rd.l3_miss.snoop_non_dram", "DEMAND_CODE_RD & L3_MISS & SNOOP_NON_DRAM"},
    {"offcore_response.demand_code_rd.l3_miss.snoop_none", "DEMAND_CODE_RD & L3_MISS & SNOOP_NONE"},
    {"offcore_response.demand_code_rd.l3_miss.snoop_not_needed", "DEMAND_CODE_RD & L3_MISS & SNOOP_NOT_NEEDED"},
    {"offcore_response.demand_code_rd.l3_miss.spl_hit", "DEMAND_CODE_RD & L3_MISS & SPL_HIT"},
    {"offcore_response.demand_code_rd.l3_miss_local_dram.any_snoop", "DEMAND_CODE_RD & L3_MISS_LOCAL_DRAM & ANY_SNOOP"},
    {"offcore_response.demand_code_rd.l3_miss_local_dram.snoop_hit_no_fwd", "DEMAND_CODE_RD & L3_MISS_LOCAL_DRAM & SNOOP_HIT_NO_FWD"},
    {"offcore_response.demand_code_rd.l3_miss_local_dram.snoop_hitm", "DEMAND_CODE_RD & L3_MISS_LOCAL_DRAM & SNOOP_HITM"},
    {"offcore_response.demand_code_rd.l3_miss_local_dram.snoop_miss", "DEMAND_CODE_RD & L3_MISS_LOCAL_DRAM & SNOOP_MISS"},
    {"offcore_response.demand_code_rd.l3_miss_local_dram.snoop_non_dram", "DEMAND_CODE_RD & L3_MISS_LOCAL_DRAM & SNOOP_NON_DRAM"},
    {"offcore_response.demand_code_rd.l3_miss_local_dram.snoop_none", "DEMAND_CODE_RD & L3_MISS_LOCAL_DRAM & SNOOP_NONE"},
    {"offcore_response.demand_code_rd.l3_miss_local_dram.snoop_not_needed", "DEMAND_CODE_RD & L3_MISS_LOCAL_DRAM & SNOOP_NOT_NEEDED"},
    {"offcore_response.demand_code_rd.l3_miss_local_dram.spl_hit", "DEMAND_CODE_RD & L3_MISS_LOCAL_DRAM & SPL_HIT"},
    {"offcore_response.demand_code_rd.l4_hit_local_l4.snoop_non_dram", "DEMAND_CODE_RD & L4_HIT_LOCAL_L4 & SNOOP_NON_DRAM"},
    {"offcore_response.demand_code_rd.supplier_none.snoop_non_dram", "DEMAND_CODE_RD & SUPPLIER_NONE & SNOOP_NON_DRAM"},
    {"offcore_response.demand_data_rd.l3_hit.snoop_non_dram", "DEMAND_DATA_RD & L3_HIT & SNOOP_NON_DRAM"},
    {"offcore_response.demand_data_rd.l3_hit_e.snoop_non_dram", "DEMAND_DATA_RD & L3_HIT_E & SNOOP_NON_DRAM"},
    {"offcore_response.demand_data_rd.l3_hit_m.snoop_non_dram", "DEMAND_DATA_RD & L3_HIT_M & SNOOP_NON_DRAM"},
    {"offcore_response.demand_data_rd.l3_hit_s.snoop_non_dram", "DEMAND_DATA_RD & L3_HIT_S & SNOOP_NON_DRAM"},
    {"offcore_response.demand_data_rd.l3_miss.any_snoop", "DEMAND_DATA_RD & L3_MISS & ANY_SNOOP"},
    {"offcore_response.demand_data_rd.l3_miss.snoop_hit_no_fwd", "DEMAND_DATA_RD & L3_MISS & SNOOP_HIT_NO_FWD"},
    {"offcore_response.demand_data_rd.l3_miss.snoop_hitm", "DEMAND_DATA_RD & L3_MISS & SNOOP_HITM"},
    {"offcore_response.demand_data_rd.l3_miss.snoop_miss", "DEMAND_DATA_RD & L3_MISS & SNOOP_MISS"},
    {"offcore_response.demand_data_rd.l3_miss.snoop_non_dram", "DEMAND_DATA_RD & L3_MISS & SNOOP_NON_DRAM"},
    {"offcore_response.demand_data_rd.l3_miss.snoop_none", "DEMAND_DATA_RD & L3_MISS & SNOOP_NONE"},
    {"offcore_response.demand_data_rd.l3_miss.snoop_not_needed", "DEMAND_DATA_RD & L3_MISS & SNOOP_NOT_NEEDED"},
    {"offcore_response.demand_data_rd.l3_miss.spl_hit", "DEMAND_DATA_RD & L3_MISS & SPL_HIT"},
    {"offcore_response.demand_data_rd.l3_miss_local_dram.any_snoop", "DEMAND_DATA_RD & L3_MISS_LOCAL_DRAM & ANY_SNOOP"},
    {"offcore_response.demand_data_rd.l3_miss_local_dram.snoop_hit_no_fwd", "DEMAND_DATA_RD & L3_MISS_LOCAL_DRAM & SNOOP_HIT_NO_FWD"},
    {"offcore_response.demand_data_rd.l3_miss_local_dram.snoop_hitm", "DEMAND_DATA_RD & L3_MISS_LOCAL_DRAM & SNOOP_HITM"},
    {"offcore_response.demand_data_rd.l3_miss_local_dram.snoop_miss", "DEMAND_DATA_RD & L3_MISS_LOCAL_DRAM & SNOOP_MISS"},
    {"offcore_response.demand_data_rd.l3_miss_local_dram.snoop_non_dram", "DEMAND_DATA_RD & L3_MISS_LOCAL_DRAM & SNOOP_NON_DRAM"},
    {"offcore_response.demand_data_rd.l3_miss_local_dram.snoop_none", "DEMAND_DATA_RD & L3_MISS_LOCAL_DRAM & SNOOP_NONE"},
    {"offcore_response.demand_data_rd.l3_miss_local_dram.snoop_not_needed", "DEMAND_DATA_RD & L3_MISS_LOCAL_DRAM & SNOOP_NOT_NEEDED"},
    {"offcore_response.demand_data_rd.l3_miss_local_dram.spl_hit", "DEMAND_DATA_RD & L3_MISS_LOCAL_DRAM & SPL_HIT"},
    {"offcore_response.demand_data_rd.l4_hit_local_l4.snoop_non_dram", "DEMAND_DATA_RD & L4_HIT_LOCAL_L4 & SNOOP_NON_DRAM"},
    {"offcore_response.demand_data_rd.supplier_none.snoop_non_dram", "DEMAND_DATA_RD & SUPPLIER_NONE & SNOOP_NON_DRAM"},
    {"offcore_response.demand_rfo.l3_hit.snoop_non_dram", "DEMAND_RFO & L3_HIT & SNOOP_NON_DRAM"},
    {"offcore_response.demand_rfo.l3_hit_e.snoop_non_dram", "DEMAND_RFO & L3_HIT_E & SNOOP_NON_DRAM"},
    {"offcore_response.demand_rfo.l3_hit_m.snoop_non_dram", "DEMAND_RFO & L3_HIT_M & SNOOP_NON_DRAM"},
    {"offcore_response.demand_rfo.l3_hit_s.snoop_non_dram", "DEMAND_RFO & L3_HIT_S & SNOOP_NON_DRAM"},
    {"offcore_response.demand_rfo.l3_miss.any_snoop", "DEMAND_RFO & L3_MISS & ANY_SNOOP"},
    {"offcore_response.demand_rfo.l3_miss.snoop_hit_no_fwd", "DEMAND_RFO & L3_MISS & SNOOP_HIT_NO_FWD"},
    {"offcore_response.demand_rfo.l3_miss.snoop_hitm", "DEMAND_RFO & L3_MISS & SNOOP_HITM"},
    {"offcore_response.demand_rfo.l3_miss.snoop_miss", "DEMAND_RFO & L3_MISS & SNOOP_MISS"},
    {"offcore_response.demand_rfo.l3_miss.snoop_non_dram", "DEMAND_RFO & L3_MISS & SNOOP_NON_DRAM"},
    {"offcore_response.demand_rfo.l3_miss.snoop_none", "DEMAND_RFO & L3_MISS & SNOOP_NONE"},
    {"offcore_response.demand_rfo.l3_miss.snoop_not_needed", "DEMAND_RFO & L3_MISS & SNOOP_NOT_NEEDED"},
    {"offcore_response.demand_rfo.l3_miss.spl_hit", "DEMAND_RFO & L3_MISS & SPL_HIT"},
    {"offcore_response.demand_rfo.l3_miss_local_dram.any_snoop", "DEMAND_RFO & L3_MISS_LOCAL_DRAM & ANY_SNOOP"},
    {"offcore_response.demand_rfo.l3_miss_local_dram.snoop_hit_no_fwd", "DEMAND_RFO & L3_MISS_LOCAL_DRAM & SNOOP_HIT_NO_FWD"},
    {"offcore_response.demand_rfo.l3_miss_local_dram.snoop_hitm", "DEMAND_RFO & L3_MISS_LOCAL_DRAM & SNOOP_HITM"},
    {"offcore_response.demand_rfo.l3_miss_local_dram.snoop_miss", "DEMAND_RFO & L3_MISS_LOCAL_DRAM & SNOOP_MISS"},
    {"offcore_response.demand_rfo.l3_miss_local_dram.snoop_non_dram", "DEMAND_RFO & L3_MISS_LOCAL_DRAM & SNOOP_NON_DRAM"},
    {"offcore_response.demand_rfo.l3_miss_local_dram.snoop_none", "DEMAND_RFO & L3_MISS_LOCAL_DRAM & SNOOP_NONE"},
    {"offcore_response.demand_rfo.l3_miss_local_dram.snoop_not_needed", "DEMAND_RFO & L3_MISS_LOCAL_DRAM & SNOOP_NOT_NEEDED"},
    {"offcore_response.demand_rfo.l3_miss_local_dram.spl_hit", "DEMAND_RFO & L3_MISS_LOCAL_DRAM & SPL_HIT"},
    {"offcore_response.demand_rfo.l4_hit_local_l4.snoop_non_dram", "DEMAND_RFO & L4_HIT_LOCAL_L4 & SNOOP_NON_DRAM"},
    {"offcore_response.demand_rfo.supplier_none.snoop_non_dram", "DEMAND_RFO & SUPPLIER_NONE & SNOOP_NON_DRAM"},
    {"offcore_response.other.l3_hit.snoop_non_dram", "OTHER & L3_HIT & SNOOP_NON_DRAM"},
    {"offcore_response.other.l3_hit_e.snoop_non_dram", "OTHER & L3_HIT_E & SNOOP_NON_DRAM"},
    {"offcore_response.other.l3_hit_m.snoop_non_dram", "OTHER & L3_HIT_M & SNOOP_NON_DRAM"},
    {"offcore_response.other.l3_hit_s.snoop_non_dram", "OTHER & L3_HIT_S & SNOOP_NON_DRAM"},
    {"offcore_response.other.l3_miss.any_snoop", "OTHER & L3_MISS & ANY_SNOOP"},
    {"offcore_response.other.l3_miss.snoop_hit_no_fwd", "OTHER & L3_MISS & SNOOP_HIT_NO_FWD"},
    {"offcore_response.other.l3_miss.snoop_hitm", "OTHER & L3_MISS & SNOOP_HITM"},
    {"offcore_response.other.l3_miss.snoop_miss", "OTHER & L3_MISS & SNOOP_MISS"},
    {"offcore_response.other.l3_miss.snoop_non_dram", "OTHER & L3_MISS & SNOOP_NON_DRAM"},
    {"offcore_response.other.l3_miss.snoop_none", "OTHER & L3_MISS & SNOOP_NONE"},
    {"offcore_response.other.l3_miss.snoop_not_needed", "OTHER & L3_MISS & SNOOP_NOT_NEEDED"},
    {"offcore_response.other.l3_miss.spl_hit", "OTHER & L3_MISS & SPL_HIT"},
    {"offcore_response.other.l3_miss_local_dram.any_snoop", "OTHER & L3_MISS_LOCAL_DRAM & ANY_SNOOP"},
    {"offcore_response.other.l3_miss_local_dram.snoop_hit_no_fwd", "OTHER & L3_MISS_LOCAL_DRAM & SNOOP_HIT_NO_FWD"},
    {"offcore_response.other.l3_miss_local_dram.snoop_hitm", "OTHER & L3_MISS_LOCAL_DRAM & SNOOP_HITM"},
    {"offcore_response.other.l3_miss_local_dram.snoop_miss", "OTHER & L3_MISS_LOCAL_DRAM & SNOOP_MISS"},
    {"offcore_response.other.l3_miss_local_dram.snoop_non_dram", "OTHER & L3_MISS_LOCAL_DRAM & SNOOP_NON_DRAM"},
    {"offcore_response.other.l3_miss_local_dram.snoop_none", "OTHER & L3_MISS_LOCAL_DRAM & SNOOP_NONE"},
    {"offcore_response.other.l3_miss_local_dram.snoop_not_needed", "OTHER & L3_MISS_LOCAL_DRAM & SNOOP_NOT_NEEDED"},
    {"offcore_response.other.l3_miss_local_dram.spl_hit", "OTHER & L3_MISS_LOCAL_DRAM & SPL_HIT"},
    {"offcore_response.other.l4_hit_local_l4.snoop_non_dram", "OTHER & L4_HIT_LOCAL_L4 & SNOOP_NON_DRAM"},
    {"offcore_response.other.supplier_none.snoop_non_dram", "OTHER & SUPPLIER_NONE & SNOOP_NON_DRAM"},
    {"offcore_response.pf_l3_data_rd.l3_hit.snoop_non_dram", "PF_L3_DATA_RD & L3_HIT & SNOOP_NON_DRAM"},
    {"offcore_response.pf_l3_data_rd.l3_hit_e.snoop_non_dram", "PF_L3_DATA_RD & L3_HIT_E & SNOOP_NON_DRAM"},
    {"offcore_response.pf_l3_data_rd.l3_hit_m.snoop_non_dram", "PF_L3_DATA_RD & L3_HIT_M & SNOOP_NON_DRAM"},
    {"offcore_response.pf_l3_data_rd.l3_hit_s.snoop_non_dram", "PF_L3_DATA_RD & L3_HIT_S & SNOOP_NON_DRAM"},
    {"offcore_response.pf_l3_data_rd.l3_miss.any_snoop", "PF_L3_DATA_RD & L3_MISS & ANY_SNOOP"},
    {"offcore_response.pf_l3_data_rd.l3_miss.snoop_hit_no_fwd", "PF_L3_DATA_RD & L3_MISS & SNOOP_HIT_NO_FWD"},
    {"offcore_response.pf_l3_data_rd.l3_miss.snoop_hitm", "PF_L3_DATA_RD & L3_MISS & SNOOP_HITM"},
    {"offcore_response.pf_l3_data_rd.l3_miss.snoop_miss", "PF_L3_DATA_RD & L3_MISS & SNOOP_MISS"},
    {"offcore_response.pf_l3_data_rd.l3_miss.snoop_non_dram", "PF_L3_DATA_RD & L3_MISS & SNOOP_NON_DRAM"},
    {"offcore_response.pf_l3_data_rd.l3_miss.snoop_none", "PF_L3_DATA_RD & L3_MISS & SNOOP_NONE"},
    {"offcore_response.pf_l3_data_rd.l3_miss.snoop_not_needed", "PF_L3_DATA_RD & L3_MISS & SNOOP_NOT_NEEDED"},
    {"offcore_response.pf_l3_data_rd.l3_miss.spl_hit", "PF_L3_DATA_RD & L3_MISS & SPL_HIT"},
    {"offcore_response.pf_l3_data_rd.l3_miss_local_dram.any_snoop", "PF_L3_DATA_RD & L3_MISS_LOCAL_DRAM & ANY_SNOOP"},
    {"offcore_response.pf_l3_data_rd.l3_miss_local_dram.snoop_hit_no_fwd", "PF_L3_DATA_RD & L3_MISS_LOCAL_DRAM & SNOOP_HIT_NO_FWD"},
    {"offcore_response.pf_l3_data_rd.l3_miss_local_dram.snoop_hitm", "PF_L3_DATA_RD & L3_MISS_LOCAL_DRAM & SNOOP_HITM"},
    {"offcore_response.pf_l3_data_rd.l3_miss_local_dram.snoop_miss", "PF_L3_DATA_RD & L3_MISS_LOCAL_DRAM & SNOOP_MISS"},
    {"offcore_response.pf_l3_data_rd.l3_miss_local_dram.snoop_non_dram", "PF_L3_DATA_RD & L3_MISS_LOCAL_DRAM & SNOOP_NON_DRAM"},
    {"offcore_response.pf_l3_data_rd.l3_miss_local_dram.snoop_none", "PF_L3_DATA_RD & L3_MISS_LOCAL_DRAM & SNOOP_NONE"},
    {"offcore_response.pf_l3_data_rd.l3_miss_local_dram.snoop_not_needed", "PF_L3_DATA_RD & L3_MISS_LOCAL_DRAM & SNOOP_NOT_NEEDED"},
    {"offcore_response.pf_l3_data_rd.l3_miss_local_dram.spl_hit", "PF_L3_DATA_RD & L3_MISS_LOCAL_DRAM & SPL_HIT"},
    {"offcore_response.pf_l3_data_rd.l4_hit_local_l4.snoop_non_dram", "PF_L3_DATA_RD & L4_HIT_LOCAL_L4 & SNOOP_NON_DRAM"},
    {"offcore_response.pf_l3_data_rd.supplier_none.snoop_non_dram", "PF_L3_DATA_RD & SUPPLIER_NONE & SNOOP_NON_DRAM"},
    {"offcore_response.pf_l3_rfo.l3_hit.snoop_non_dram", "PF_L3_RFO & L3_HIT & SNOOP_NON_DRAM"},
    {"offcore_response.pf_l3_rfo.l3_hit_e.snoop_non_dram", "PF_L3_RFO & L3_HIT_E & SNOOP_NON_DRAM"},
    {"offcore_response.pf_l3_rfo.l3_hit_m.snoop_non_dram", "PF_L3_RFO & L3_HIT_M & SNOOP_NON_DRAM"},
    {"offcore_response.pf_l3_rfo.l3_hit_s.snoop_non_dram", "PF_L3_RFO & L3_HIT_S & SNOOP_NON_DRAM"},
    {"offcore_response.pf_l3_rfo.l3_miss.any_snoop", "PF_L3_RFO & L3_MISS & ANY_SNOOP"},
    {"offcore_response.pf_l3_rfo.l3_miss.snoop_hit_no_fwd", "PF_L3_RFO & L3_MISS & SNOOP_HIT_NO_FWD"},
    {"offcore_response.pf_l3_rfo.l3_miss.snoop_hitm", "PF_L3_RFO & L3_MISS & SNOOP_HITM"},
    {"offcore_response.pf_l3_rfo.l3_miss.snoop_miss", "PF_L3_RFO & L3_MISS & SNOOP_MISS"},
    {"offcore_response.pf_l3_rfo.l3_miss.snoop_non_dram", "PF_L3_RFO & L3_MISS & SNOOP_NON_DRAM"},
    {"offcore_response.pf_l3_rfo.l3_miss.snoop_none", "PF_L3_RFO & L3_MISS & SNOOP_NONE"},
    {"offcore_response.pf_l3_rfo.l3_miss.snoop_not_needed", "PF_L3_RFO & L3_MISS & SNOOP_NOT_NEEDED"},
    {"offcore_response.pf_l3_rfo.l3_miss.spl_hit", "PF_L3_RFO & L3_MISS & SPL_HIT"},
    {"offcore_response.pf_l3_rfo.l3_miss_local_dram.any_snoop", "PF_L3_RFO & L3_MISS_LOCAL_DRAM & ANY_SNOOP"},
    {"offcore_response.pf_l3_rfo.l3_miss_local_dram.snoop_hit_no_fwd", "PF_L3_RFO & L3_MISS_LOCAL_DRAM & SNOOP_HIT_NO_FWD"},
    {"offcore_response.pf_l3_rfo.l3_miss_local_dram.snoop_hitm", "PF_L3_RFO & L3_MISS_LOCAL_DRAM & SNOOP_HITM"},
    {"offcore_response.pf_l3_rfo.l3_miss_local_dram.snoop_miss", "PF_L3_RFO & L3_MISS_LOCAL_DRAM & SNOOP_MISS"},
    {"offcore_response.pf_l3_rfo.l3_miss_local_dram.snoop_non_dram", "PF_L3_RFO & L3_MISS_LOCAL_DRAM & SNOOP_NON_DRAM"},
    {"offcore_response.pf_l3_rfo.l3_miss_local_dram.snoop_none", "PF_L3_RFO & L3_MISS_LOCAL_DRAM & SNOOP_NONE"},
    {"offcore_response.pf_l3_rfo.l3_miss_local_dram.snoop_not_needed", "PF_L3_RFO & L3_MISS_LOCAL_DRAM & SNOOP_NOT_NEEDED"},
    {"offcore_response.pf_l3_rfo.l3_miss_local_dram.spl_hit", "PF_L3_RFO & L3_MISS_LOCAL_DRAM & SPL_HIT"},
    {"offcore_response.pf_l3_rfo.l4_hit_local_l4.snoop_non_dram", "PF_L3_RFO & L4_HIT_LOCAL_L4 & SNOOP_NON_DRAM"},
    {"offcore_response.pf_l3_rfo.supplier_none.snoop_non_dram", "PF_L3_RFO & SUPPLIER_NONE & SNOOP_NON_DRAM"},
    {"offcore_response.streaming_stores.l3_hit.snoop_non_dram", "STREAMING_STORES & L3_HIT & SNOOP_NON_DRAM"},
    {"offcore_response.streaming_stores.l3_hit_e.snoop_non_dram", "STREAMING_STORES & L3_HIT_E & SNOOP_NON_DRAM"},
    {"offcore_response.streaming_stores.l3_hit_m.snoop_non_dram", "STREAMING_STORES & L3_HIT_M & SNOOP_NON_DRAM"},
    {"offcore_response.streaming_stores.l3_hit_s.snoop_non_dram", "STREAMING_STORES & L3_HIT_S & SNOOP_NON_DRAM"},
    {"offcore_response.streaming_stores.l3_miss.any_snoop", "STREAMING_STORES & L3_MISS & ANY_SNOOP"},
    {"offcore_response.streaming_stores.l3_miss.snoop_hit_no_fwd", "STREAMING_STORES & L3_MISS & SNOOP_HIT_NO_FWD"},
    {"offcore_response.streaming_stores.l3_miss.snoop_hitm", "STREAMING_STORES & L3_MISS & SNOOP_HITM"},
    {"offcore_response.streaming_stores.l3_miss.snoop_miss", "STREAMING_STORES & L3_MISS & SNOOP_MISS"},
    {"offcore_response.streaming_stores.l3_miss.snoop_non_dram", "STREAMING_STORES & L3_MISS & SNOOP_NON_DRAM"},
    {"offcore_response.streaming_stores.l3_miss.snoop_none", "STREAMING_STORES & L3_MISS & SNOOP_NONE"},
    {"offcore_response.streaming_stores.l3_miss.snoop_not_needed", "STREAMING_STORES & L3_MISS & SNOOP_NOT_NEEDED"},
    {"offcore_response.streaming_stores.l3_miss.spl_hit", "STREAMING_STORES & L3_MISS & SPL_HIT"},
    {"offcore_response.streaming_stores.l3_miss_local_dram.any_snoop", "STREAMING_STORES & L3_MISS_LOCAL_DRAM & ANY_SNOOP"},
    {"offcore_response.streaming_stores.l3_miss_local_dram.snoop_hit_no_fwd", "STREAMING_STORES & L3_MISS_LOCAL_DRAM & SNOOP_HIT_NO_FWD"},
    {"offcore_response.streaming_stores.l3_miss_local_dram.snoop_hitm", "STREAMING_STORES & L3_MISS_LOCAL_DRAM & SNOOP_HITM"},
    {"offcore_response.streaming_stores.l3_miss_local_dram.snoop_miss", "STREAMING_STORES & L3_MISS_LOCAL_DRAM & SNOOP_MISS"},
    {"offcore_response.streaming_stores.l3_miss_local_dram.snoop_non_dram", "STREAMING_STORES & L3_MISS_LOCAL_DRAM & SNOOP_NON_DRAM"},
    {"offcore_response.streaming_stores.l3_miss_local_dram.snoop_none", "STREAMING_STORES & L3_MISS_LOCAL_DRAM & SNOOP_NONE"},
    {"offcore_response.streaming_stores.l3_miss_local_dram.snoop_not_needed", "STREAMING_STORES & L3_MISS_LOCAL_DRAM & SNOOP_NOT_NEEDED"},
    {"offcore_response.streaming_stores.l3_miss_local_dram.spl_hit", "STREAMING_STORES & L3_MISS_LOCAL_DRAM & SPL_HIT"},
    {"offcore_response.streaming_stores.l4_hit_local_l4.snoop_non_dram", "STREAMING_STORES & L4_HIT_LOCAL_L4 & SNOOP_NON_DRAM"},
    {"offcore_response.streaming_stores.supplier_none.snoop_non_dram", "STREAMING_STORES & SUPPLIER_NONE & SNOOP_NON_DRAM"},
    {"rtm_retired.aborted", "Number of times an RTM execution aborted due to any reasons (multiple categories may count as one) (Precise event)"},
    {"rtm_retired.aborted_events", "Number of times an RTM execution aborted due to none of the previous 4 categories (e.g. interrupt)"},
    {"rtm_retired.aborted_mem", "Number of times an RTM execution aborted due to various memory events (e.g. read/write capacity and conflicts)"},
    {"rtm_retired.aborted_memtype", "Number of times an RTM execution aborted due to incompatible memory type"},
    {"rtm_retired.aborted_timer", "Number of times an RTM execution aborted due to uncommon conditions"},
    {"rtm_retired.aborted_unfriendly", "Number of times an RTM execution aborted due to HLE-unfriendly instructions"},
    {"rtm_retired.commit", "Number of times an RTM execution successfully committed"},
    {"rtm_retired.start", "Number of times an RTM execution started"},
    {"tx_exec.misc1", "Counts the number of times a class of instructions that may cause a transactional abort was executed. Since this is the count of execution, it may not always cause a transactional abort"},
    {"tx_exec.misc2", "Counts the number of times a class of instructions (e.g., vzeroupper) that may cause a transactional abort was executed inside a transactional region"},
    {"tx_exec.misc3", "Counts the number of times an instruction execution caused the transactional nest count supported to be exceeded"},
    {"tx_exec.misc4", "Counts the number of times a XBEGIN instruction was executed inside an HLE transactional region"},
    {"tx_exec.misc5", "Counts the number of times an HLE XACQUIRE instruction was executed inside an RTM transactional region"},
    {"tx_mem.abort_capacity", "Number of times a transactional abort was signaled due to a data capacity limitation for transactional reads or writes"},
    {"tx_mem.abort_conflict", "Number of times a transactional abort was signaled due to a data conflict on a transactionally accessed address"},
    {"tx_mem.abort_hle_elision_buffer_mismatch", "Number of times an HLE transactional execution aborted due to XRELEASE lock not satisfying the address and value requirements in the elision buffer"},
    {"tx_mem.abort_hle_elision_buffer_not_empty", "Number of times an HLE transactional execution aborted due to NoAllocatedElisionBuffer being non-zero"},
    {"tx_mem.abort_hle_elision_buffer_unsupported_alignment", "Number of times an HLE transactional execution aborted due to an unsupported read alignment from the elision buffer"},
    {"tx_mem.abort_hle_store_to_elided_lock", "Number of times a HLE transactional region aborted due to a non XRELEASE prefixed instruction writing to an elided lock in the elision buffer"},
    {"tx_mem.hle_elision_buffer_full", "Number of times HLE lock could not be elided due to ElisionBufferAvailable being zero"},
    {"hw_interrupts.received", "Number of hardware interrupts received by the processor"},
    {"arith.divider_active", "Cycles when divide unit is busy executing divide or square root operations. Accounts for integer and floating-point operations"},
    {"baclears.any", "Counts the total number when the front end is resteered, mainly when the BPU cannot provide a correct prediction and this is corrected by other branch handling mechanisms at the front end"},
    {"br_inst_retired.all_branches", "All (macro) branch instructions retired Spec update: SKL091"},
    {"br_inst_retired.all_branches_pebs", "All (macro) branch instructions retired Spec update: SKL091 (Must be precise)"},
    {"br_inst_retired.conditional", "Conditional branch instructions retired Spec update: SKL091 (Precise event)"},
    {"br_inst_retired.far_branch", "Far branch instructions retired Spec update: SKL091 (Precise event)"},
    {"br_inst_retired.near_call", "Direct and indirect near call instructions retired Spec update: SKL091 (Precise event)"},
    {"br_inst_retired.near_return", "Return instructions retired Spec update: SKL091 (Precise event)"},
    {"br_inst_retired.near_taken", "Taken branch instructions retired Spec update: SKL091 (Precise event)"},
    {"br_inst_retired.not_taken", "Not taken branch instructions retired Spec update: SKL091"},
    {"br_misp_retired.all_branches", "All mispredicted macro branch instructions retired"},
    {"br_misp_retired.all_branches_pebs", "Mispredicted macro branch instructions retired (Must be precise)"},
    {"br_misp_retired.conditional", "Mispredicted conditional branch instructions retired (Precise event)"},
    {"br_misp_retired.near_call", "Mispredicted direct and indirect near call instructions retired (Precise event)"},
    {"br_misp_retired.near_taken", "Number of near branch instructions retired that were mispredicted and taken (Precise event)"},
    {"cpu_clk_thread_unhalted.one_thread_active", "Core crystal clock cycles when this thread is unhalted and the other thread is halted"},
    {"cpu_clk_thread_unhalted.ref_xclk", "Core crystal clock cycles when the thread is unhalted"},
    {"cpu_clk_thread_unhalted.ref_xclk_any", "Core crystal clock cycles when at least one thread on the physical core is unhalted"},
    {"cpu_clk_unhalted.one_thread_active", "Core crystal clock cycles when this thread is unhalted and the other thread is halted"},
    {"cpu_clk_unhalted.ref_tsc", "Reference cycles when the core is not in halt state"},
    {"cpu_clk_unhalted.ref_xclk", "Core crystal clock cycles when the thread is unhalted"},
    {"cpu_clk_unhalted.ref_xclk_any", "Core crystal clock cycles when at least one thread on the physical core is unhalted"},
    {"cpu_clk_unhalted.ring0_trans", "Counts when there is a transition from ring 1, 2 or 3 to ring 0"},
    {"cpu_clk_unhalted.thread", "Core cycles when the thread is not in halt state"},
    {"cpu_clk_unhalted.thread_any", "Core cycles when at least one thread on the physical core is not in halt state"},
    {"cpu_clk_unhalted.thread_p", "Thread cycles when thread is not in halt state"},
    {"cpu_clk_unhalted.thread_p_any", "Core cycles when at least one thread on the physical core is not in halt state"},
    {"cycle_activity.cycles_l1d_miss", "Cycles while L1 cache miss demand load is outstanding"},
    {"cycle_activity.cycles_l2_miss", "Cycles while L2 cache miss demand load is outstanding"},
    {"cycle_activity.cycles_mem_any", "Cycles while memory subsystem has an outstanding load"},
    {"cycle_activity.stalls_l1d_miss", "Execution stalls while L1 cache miss demand load is outstanding"},
    {"cycle_activity.stalls_l2_miss", "Execution stalls while L2 cache miss demand load is outstanding"},
    {"cycle_activity.stalls_mem_any", "Execution stalls while memory subsystem has an outstanding load"},
    {"cycle_activity.stalls_total", "Total execution stalls"},
    {"exe_activity.1_ports_util", "Cycles total of 1 uop is executed on all ports and Reservation Station was not empty"},
    {"exe_activity.2_ports_util", "Cycles total of 2 uops are executed on all ports and Reservation Station was not empty"},
    {"exe_activity.3_ports_util", "Cycles total of 3 uops are executed on all ports and Reservation Station was not empty"},
    {"exe_activity.4_ports_util", "Cycles total of 4 uops are executed on all ports and Reservation Station was not empty"},
    {"exe_activity.bound_on_stores", "Cycles where the Store Buffer was full and no outstanding load"},
    {"exe_activity.exe_bound_0_ports", "Cycles where no uops were executed, the Reservation Station was not empty, the Store Buffer was full and there was no outstanding load"},
    {"ild_stall.lcp", "Stalls caused by changing prefix length of the instruction"},
    {"inst_retired.any", "Instructions retired from execution"},
    {"inst_retired.any_p", "Number of instructions retired. General Counter - architectural event Spec update: SKL091, SKL044"},
    {"inst_retired.prec_dist", "Precise instruction retired event with HW to reduce effect of PEBS shadow in IP distribution Spec update: SKL091, SKL044 (Must be precise)"},
    {"inst_retired.total_cycles_ps", "Number of cycles using always true condition applied to PEBS instructions retired event Spec update: SKL091, SKL044 (Must be precise)"},
    {"int_misc.clear_resteer_cycles", "Cycles the issue-stage is waiting for front-end to fetch from resteered path following branch misprediction or machine clear events"},
    {"int_misc.recovery_cycles", "Core cycles the allocator was stalled due to recovery from earlier clear event for this thread (e.g. misprediction or memory nuke)"},
    {"int_misc.recovery_cycles_any", "Core cycles the allocator was stalled due to recovery from earlier clear event for any thread running on the physical core (e.g. misprediction or memory nuke)"},
    {"ld_blocks.no_sr", "The number of times that split load operations are temporarily blocked because all resources for handling the split accesses are in use"},
    {"ld_blocks.store_forward", "Loads blocked by overlapping with store buffer that cannot be forwarded"},
    {"ld_blocks_partial.address_alias", "False dependencies in MOB due to partial compare on address"},
    {"load_hit_pre.sw_pf", "Demand load dispatches that hit L1D fill buffer (FB) allocated for software prefetch"},
    {"lsd.cycles_4_uops", "Cycles 4 Uops delivered by the LSD, but didn't come from the decoder"},
    {"lsd.cycles_active", "Cycles Uops delivered by the LSD, but didn't come from the decoder"},
    {"lsd.uops", "Number of Uops delivered by the LSD"},
    {"machine_clears.count", "Number of machine clears (nukes) of any type"},
    {"machine_clears.smc", "Self-modifying code (SMC) detected"},
    {"other_assists.any", "Number of times a microcode assist is invoked by HW other than FP-assist. Examples include AD (page Access Dirty) and AVX* related assists"},
    {"resource_stalls.any", "Resource-related stall cycles"},
    {"resource_stalls.sb", "Cycles stalled due to no store buffers available. (not including draining form sync)"},
    {"rob_misc_events.lbr_inserts", "Increments whenever there is an update to the LBR array"},
    {"rs_events.empty_cycles", "Cycles when Reservation Station (RS) is empty for the thread"},
    {"rs_events.empty_end", "Counts end of periods where the Reservation Station (RS) was empty. Could be useful to precisely locate Frontend Latency Bound issues"},
    {"uops_dispatched_port.port_0", "Cycles per thread when uops are executed in port 0"},
    {"uops_dispatched_port.port_1", "Cycles per thread when uops are executed in port 1"},
    {"uops_dispatched_port.port_2", "Cycles per thread when uops are executed in port 2"},
    {"uops_dispatched_port.port_3", "Cycles per thread when uops are executed in port 3"},
    {"uops_dispatched_port.port_4", "Cycles per thread when uops are executed in port 4"},
    {"uops_dispatched_port.port_5", "Cycles per thread when uops are executed in port 5"},
    {"uops_dispatched_port.port_6", "Cycles per thread when uops are executed in port 6"},
    {"uops_dispatched_port.port_7", "Cycles per thread when uops are executed in port 7"},
    {"uops_executed.core", "Number of uops executed on the core"},
    {"uops_executed.core_cycles_ge_1", "Cycles at least 1 micro-op is executed from any thread on physical core"},
    {"uops_executed.core_cycles_ge_2", "Cycles at least 2 micro-op is executed from any thread on physical core"},
    {"uops_executed.core_cycles_ge_3", "Cycles at least 3 micro-op is executed from any thread on physical core"},
    {"uops_executed.core_cycles_ge_4", "Cycles at least 4 micro-op is executed from any thread on physical core"},
    {"uops_executed.core_cycles_none", "Cycles with no micro-ops executed from any thread on physical core"},
    {"uops_executed.cycles_ge_1_uop_exec", "Cycles where at least 1 uop was executed per-thread"},
    {"uops_executed.cycles_ge_2_uops_exec", "Cycles where at least 2 uops were executed per-thread"},
    {"uops_executed.cycles_ge_3_uops_exec", "Cycles where at least 3 uops were executed per-thread"},
    {"uops_executed.cycles_ge_4_uops_exec", "Cycles where at least 4 uops were executed per-thread"},
    {"uops_executed.stall_cycles", "Counts number of cycles no uops were dispatched to be executed on this thread"},
    {"uops_executed.thread", "Counts the number of uops to be executed per-thread each cycle"},
    {"uops_executed.x87", "Counts the number of x87 uops dispatched"},
    {"uops_issued.any", "Uops that Resource Allocation Table (RAT) issues to Reservation Station (RS)"},
    {"uops_issued.slow_lea", "Number of slow LEA uops being allocated. A uop is generally considered SlowLea if it has 3 sources (e.g. 2 sources + immediate) regardless if as a result of LEA instruction or not"},
    {"uops_issued.stall_cycles", "Cycles when Resource Allocation Table (RAT) does not issue Uops to Reservation Station (RS) for the thread"},
    {"uops_issued.vector_width_mismatch", "Uops inserted at issue-stage in order to preserve upper bits of vector registers"},
    {"uops_retired.retire_slots", "Retirement slots used"},
    {"uops_retired.stall_cycles", "Cycles without actually retired uops"},
    {"uops_retired.total_cycles", "Cycles with less than 10 actually retired uops"},
    {"unc_arb_coh_trk_requests.all", "Unit: uncore_arb Number of entries allocated. Account for Any type: e.g. Snoop, Core aperture, etc"},
    {"unc_arb_trk_occupancy.all", "Unit: uncore_arb Each cycle count number of all Core outgoing valid entries. Such entry is defined as valid from its allocation till first of IDI0 or DRS0 messages is sent out. Accounts for Coherent and non-coherent traffic"},
    {"unc_arb_trk_occupancy.cycles_with_any_request", "Unit: uncore_arb Cycles with at least one request outstanding is waiting for data return from memory controller. Account for coherent and non-coherent requests initiated by IA Cores, Processor Graphics Unit, or LLC.;"},
    {"unc_arb_trk_requests.all", "Unit: uncore_arb Total number of Core outgoing entries allocated. Accounts for Coherent and non-coherent traffic"},
    {"unc_arb_trk_requests.drd_direct", "Unit: uncore_arb Number of Core coherent Data Read entries allocated in DirectData mode"},
    {"unc_arb_trk_requests.writes", "Unit: uncore_arb Number of Writes allocated - any write transactions: full/partials writes and evictions"},
    {"unc_cbo_cache_lookup.any_es", "Unit: uncore_cbox L3 Lookup any request that access cache and found line in E or S-state"},
    {"unc_cbo_cache_lookup.any_i", "Unit: uncore_cbox L3 Lookup any request that access cache and found line in I-state"},
    {"unc_cbo_cache_lookup.any_m", "Unit: uncore_cbox L3 Lookup any request that access cache and found line in M-state"},
    {"unc_cbo_cache_lookup.any_mesi", "Unit: uncore_cbox L3 Lookup any request that access cache and found line in MESI-state"},
    {"unc_cbo_cache_lookup.read_es", "Unit: uncore_cbox L3 Lookup read request that access cache and found line in E or S-state"},
    {"unc_cbo_cache_lookup.read_i", "Unit: uncore_cbox L3 Lookup read request that access cache and found line in I-state"},
    {"unc_cbo_cache_lookup.read_mesi", "Unit: uncore_cbox L3 Lookup read request that access cache and found line in any MESI-state"},
    {"unc_cbo_cache_lookup.write_es", "Unit: uncore_cbox L3 Lookup write request that access cache and found line in E or S-state"},
    {"unc_cbo_cache_lookup.write_m", "Unit: uncore_cbox L3 Lookup write request that access cache and found line in M-state"},
    {"unc_cbo_cache_lookup.write_mesi", "Unit: uncore_cbox L3 Lookup write request that access cache and found line in MESI-state"},
    {"unc_cbo_xsnp_response.hit_xcore", "Unit: uncore_cbox A cross-core snoop initiated by this Cbox due to processor core memory request which hits a non-modified line in some processor core"},
    {"unc_cbo_xsnp_response.hitm_xcore", "Unit: uncore_cbox A cross-core snoop initiated by this Cbox due to processor core memory request which hits a modified line in some processor core"},
    {"unc_cbo_xsnp_response.miss_eviction", "Unit: uncore_cbox A cross-core snoop resulted from L3 Eviction which misses in some processor core"},
    {"unc_cbo_xsnp_response.miss_xcore", "Unit: uncore_cbox A cross-core snoop initiated by this Cbox due to processor core memory request which misses in some processor core"},
    {"dtlb_load_misses.miss_causes_a_walk", "Load misses in all DTLB levels that cause page walks"},
    {"dtlb_load_misses.stlb_hit", "Loads that miss the DTLB and hit the STLB"},
    {"dtlb_load_misses.walk_active", "Cycles when at least one PMH is busy with a page walk for a load. EPT page walk duration are excluded in Skylake"},
    {"dtlb_load_misses.walk_completed", "Load miss in all TLB levels causes a page walk that completes. (All page sizes)"},
    {"dtlb_load_misses.walk_completed_1g", "Load miss in all TLB levels causes a page walk that completes. (1G)"},
    {"dtlb_load_misses.walk_completed_2m_4m", "Demand load Miss in all translation lookaside buffer (TLB) levels causes a page walk that completes (2M/4M)"},
    {"dtlb_load_misses.walk_completed_4k", "Demand load Miss in all translation lookaside buffer (TLB) levels causes a page walk that completes (4K)"},
    {"dtlb_load_misses.walk_pending", "Counts 1 per cycle for each PMH that is busy with a page walk for a load. EPT page walk duration are excluded in Skylake"},
    {"dtlb_store_misses.miss_causes_a_walk", "Store misses in all DTLB levels that cause page walks"},
    {"dtlb_store_misses.stlb_hit", "Stores that miss the DTLB and hit the STLB"},
    {"dtlb_store_misses.walk_active", "Cycles when at least one PMH is busy with a page walk for a store. EPT page walk duration are excluded in Skylake"},
    {"dtlb_store_misses.walk_completed", "Store misses in all TLB levels causes a page walk that completes. (All page sizes)"},
    {"dtlb_store_misses.walk_completed_1g", "Store misses in all DTLB levels that cause completed page walks (1G)"},
    {"dtlb_store_misses.walk_completed_2m_4m", "Store misses in all DTLB levels that cause completed page walks (2M/4M)"},
    {"dtlb_store_misses.walk_completed_4k", "Store miss in all TLB levels causes a page walk that completes. (4K)"},
    {"dtlb_store_misses.walk_pending", "Counts 1 per cycle for each PMH that is busy with a page walk for a store. EPT page walk duration are excluded in Skylake"},
    {"ept.walk_pending", "Counts 1 per cycle for each PMH that is busy with a EPT (Extended Page Table) walk for any request type"},
    {"itlb.itlb_flush", "Flushing of the Instruction TLB (ITLB) pages, includes 4k/2M/4M pages"},
    {"itlb_misses.miss_causes_a_walk", "Misses at all ITLB levels that cause page walks"},
    {"itlb_misses.stlb_hit", "Instruction fetch requests that miss the ITLB and hit the STLB"},
    {"itlb_misses.walk_active", "Cycles when at least one PMH is busy with a page walk for code (instruction fetch) request. EPT page walk duration are excluded in Skylake"},
    {"itlb_misses.walk_completed", "Code miss in all TLB levels causes a page walk that completes. (All page sizes)"},
    {"itlb_misses.walk_completed_1g", "Code miss in all TLB levels causes a page walk that completes. (1G)"},
    {"itlb_misses.walk_completed_2m_4m", "Code miss in all TLB levels causes a page walk that completes. (2M/4M)"},
    {"itlb_misses.walk_completed_4k", "Code miss in all TLB levels causes a page walk that completes. (4K)"},
    {"itlb_misses.walk_pending", "Counts 1 per cycle for each PMH that is busy with a page walk for an instruction fetch request. EPT page walk duration are excluded in Skylake"},
    {"tlb_flush.dtlb_thread", "DTLB flush attempts of the thread-specific entries"},
    {"tlb_flush.stlb_any", "STLB flush attempts"},
};
    
internal int
IsWhitespace(char Char)
{
    int Result = ((Char == '\t') ||
                  (Char == ' ') ||
                  (Char == '\r') ||
                  (Char == '\n'));
    return(Result);
}

internal void
CleanWhitespace(char *At)
{
    char *Dest = At;
    char *Source = At;
    while(IsWhitespace(Source[0])) {++Source;}
    
    while(*Source)
    {
        if(IsWhitespace(Source[0]))
        {
            while(IsWhitespace(Source[0])) {++Source;}
            if(Source[0])
            {
                *Dest++ = ' ';
            }
        }
        else
        {
            *Dest++ = *Source++;
        }
    }
    
    if(Dest != Source)
    {
        *Dest = 0;
    }
}

internal void
ImportCounterList(void)
{
    FILE *Input = fopen("input.txt", "rb");
    if(Input)
    {
        fseek(Input, 0, SEEK_END);
        size_t Size = ftell(Input);
        fseek(Input, 0, SEEK_SET);
        char *Temp = (char *)malloc(Size + 1);
        fread(Temp, Size, 1, Input);
        Temp[Size] = 0;
        
        char *At = Temp;
        for(;;)
        {
            char *IDLeft = At;
            while(At[0] && (At[0] != '[')) {++At;}
            char *DescLeft = At;
            while(At[0] && (At[0] != ']')) {++At;}
            char *DescRight = At;
            
            if(DescRight[0])
            {
                char *ID = IDLeft;
                while(ID[0] && IsWhitespace(ID[0])) {++ID;}
                char *End = ID;
                while(End[0] && !IsWhitespace(End[0])) {++End;}
                End[0] = 0;
                
                char *Description = (DescLeft + 1);
                DescRight[0] = 0;

                CleanWhitespace(ID);
                CleanWhitespace(Description);

                fprintf(stdout, "    {\"%s\", \"%s\"},\n", ID, Description);
                
                ++At;
            }
            else
            {
                break;
            }
        }
        
        fclose(Input);
    }
    else
    {
        fprintf(stderr, "ERROR: Unable to open input.txt\n");
    }
}

struct sort_data
{
	int CounterIndex;
	f64 Key;
};

internal int
SortDataCompare(const void *AInit, const void *BInit)
{
    sort_data *A = (sort_data *)AInit;
    sort_data *B = (sort_data *)BInit;

    int Result = 0;
    if(A->Key < B->Key)
    {
        Result = -1;
    }
    else if(A->Key > B->Key)
    {
        Result = 1;
    }

    return(Result);
}

int
main(int ArgCount, char **Args)
{
    fprintf(stderr, "Exquisite Cream Sauce v0.1 (Sauce à la Crème Exquise)\n");
    fprintf(stderr, "USE AT YOUR OWN RISK.\n");
    fprintf(stderr, "\n");

    sort_data SortData[ArrayCount(CounterSpecs)] = {};

    int CounterCount = ArrayCount(CounterSpecs);    
    if(ArgCount >= 2)
    {
        int ExeCount = ArgCount - 1;
        counter_stat **ExeStats = (counter_stat **)malloc(ExeCount * sizeof(counter_stat *));
        size_t StatsSize = CounterCount * sizeof(counter_stat);
        for(int ExeIndex = 0;
            ExeIndex < ExeCount;
            ++ExeIndex)
        {
            int ArgIndex = ExeIndex + 1;
            counter_stat *Stats = (counter_stat *)malloc(StatsSize);
            memset(Stats, 0, StatsSize);
            ExeStats[ExeIndex] = Stats;

            for(int BaseSpecIndex = 0;
                BaseSpecIndex < CounterCount;
                BaseSpecIndex += 4)
            {
                fprintf(stderr, "[%d/%d].[%d/%d]            \r", ExeIndex + 1, ExeCount, BaseSpecIndex + 1, CounterCount);

                char Counters[1024];
                Counters[0] = 0;
                for(int SpecOffset = 0;
                    SpecOffset < 4;
                    ++SpecOffset)
                {
                    int SpecIndex = BaseSpecIndex + SpecOffset;
                    if(SpecIndex < CounterCount)
                    {
                        if(SpecOffset != 0)
                        {
                            strcat(Counters, ",");
                        }
                        
                        counter_spec *Spec = CounterSpecs + SpecIndex;
                        strcat(Counters, Spec->ID);
                    }
                }
                
                char *TempFile = "__xcs_temp.csv";
                char *Executable = Args[ArgIndex];
                char *Delim = ";";
                char Command[1024];
                snprintf(Command, sizeof(Command), "perf stat -o %s -x\"%s\" -e %s \"%s\"", TempFile, Delim, Counters, Executable);
                system(Command);
                
                FILE *In = fopen(TempFile, "r");
                if(In)
                {
                    char Buf[1024];
                    // NOTE(casey): Skip two lines, because we can't get perf to not write them :/
                    fgets(Buf, sizeof(Buf), In);
                    fgets(Buf, sizeof(Buf), In);
                    for(int SpecOffset = 0;
                        SpecOffset < 4;
                        ++SpecOffset)
                    {
                        int SpecIndex = BaseSpecIndex + SpecOffset;
                        if(SpecIndex < CounterCount)
                        {
                            counter_stat *Stat = Stats + SpecIndex;
                            
                            fgets(Buf, sizeof(Buf), In);
                            sscanf(Buf, "%llu", &Stat->Value);
                        }
                    }
                    fclose(In);
                }
                else
                {
                    fprintf(stderr, "ERROR: Unable to open test file.\n");
                }
            }
        }
        fprintf(stderr, "\n");

        for(int SpecIndex = 0;
            SpecIndex < CounterCount;
            ++SpecIndex)
        {
            counter_spec *Spec = CounterSpecs + SpecIndex;
                
            f64 Accum = 0;
            for(int ExeIndex = 0;
                ExeIndex < ExeCount;
                ++ExeIndex)
            {
                counter_stat *Stat = ExeStats[ExeIndex] + SpecIndex;
                Accum += (f64)Stat->Value;
            }
            
            f64 Average = (Accum / (f64)ExeCount);
            f64 HighestRatio = 0;
            if(Average)
            {
                for(int ExeIndex = 0;
                    ExeIndex < ExeCount;
                    ++ExeIndex)
                {
                    counter_stat *Stat = ExeStats[ExeIndex] + SpecIndex;
                    f64 Diff = (fabs((f64)Stat->Value - Average) / Average);
                    if(HighestRatio < Diff)
                    {
                        HighestRatio = Diff;
                    }
                }
            }
            SortData[SpecIndex].Key = HighestRatio;
            SortData[SpecIndex].CounterIndex = SpecIndex;
        }

	qsort(SortData, CounterCount, sizeof(SortData[0]), SortDataCompare);
        for(int ExeIndex = 0;
            ExeIndex < ExeCount;
            ++ExeIndex)
        {
            fprintf(stdout, "\"%s\",", Args[1 + ExeIndex]);
        }
        fprintf(stdout, "Counter,Description\n");

        for(int SortIndex = 0;
            SortIndex < CounterCount;
            ++SortIndex)
        {
            int SpecIndex = SortData[SortIndex].CounterIndex;
            counter_spec *Spec = CounterSpecs + SpecIndex;
            for(int ExeIndex = 0;
                ExeIndex < ExeCount;
                ++ExeIndex)
            {
                counter_stat *Stat = ExeStats[ExeIndex] + SpecIndex;
                fprintf(stdout, "%llu,", (u64)Stat->Value);
            }
            
            fprintf(stdout, "%s,\"%s\"\n", Spec->ID, Spec->Description);
        }
    }
    else
    {
        fprintf(stdout, "Usage: %s <exe 1> <exe 2> ...\n", Args[0]);
    }
    
    return(0);
}

/*
internal counter_spec
CounterSpecs[] =
{
    {"cycles", "Total cycle count"},
    {"instructions", "Total instruction count"},
    {"ARITH.DIVIDER_ACTIVE", "Cycles when divide unit is busy executing divide or square root operations. Accounts for integer and floating-point operations."},
    {"BACLEARS.ANY", "Counts the number of times the front-end is resteered when it finds a branch instruction in a fetch line. This occurs for the first time a branch instruction is fetched or when the branch is not tracked by the BPU (Branch Prediction Unit) anymore."},
    {"BR_INST_RETIRED.ALL_BRANCHES", "Counts all (macro) branch instructions retired."},
    {"BR_INST_RETIRED.ALL_BRANCHES_PS", "This is a precise version of BR_INST_RETIRED.ALL_BRANCHES that counts all (macro) branch instructions retired."},
    {"BR_INST_RETIRED.CONDITIONAL", "This event counts conditional branch instructions retired."},
    {"BR_INST_RETIRED.CONDITIONAL_PS", "This is a precise version (that is, uses PEBS) of the event that counts conditional branch instructions retired."},
    {"BR_INST_RETIRED.FAR_BRANCH", "This event counts far branch instructions retired."},
    {"BR_INST_RETIRED.FAR_BRANCH_PS", "This is a precise version (that is, uses PEBS) of the event that counts far branch instructions retired."},
    {"BR_INST_RETIRED.NEAR_CALL", "This event counts both direct and indirect near call instructions retired."},
    {"BR_INST_RETIRED.NEAR_CALL_PS", "This is a precise version (that is, uses PEBS) of the event that counts both direct and indirect near call instructions retired."},
    {"BR_INST_RETIRED.NEAR_RETURN", "This event counts return instructions retired."},
    {"BR_INST_RETIRED.NEAR_RETURN_PS", "This is a precise version (that is, uses PEBS) of the event that counts return instructions retired."},
    {"BR_INST_RETIRED.NEAR_TAKEN", "This event counts taken branch instructions retired."},
    {"BR_INST_RETIRED.NEAR_TAKEN_PS", "This is a precise version (that is, uses PEBS) of the event that counts taken branch instructions retired."},
    {"BR_INST_RETIRED.NOT_TAKEN", "This event counts not taken branch instructions retired."},
    {"BR_MISP_RETIRED.ALL_BRANCHES", "Counts all the retired branch instructions that were mispredicted by the processor. A branch misprediction occurs when the processor incorrectly predicts the destination of the branch. When the misprediction is discovered at execution, all the instructions executed in the wrong (speculative) path must be discarded, and the processor must start fetching from the correct path."},
    {"BR_MISP_RETIRED.ALL_BRANCHES_PS", "This is a precise version of BR_MISP_RETIRED.ALL_BRANCHES that counts all mispredicted macro branch instructions retired."},
    {"BR_MISP_RETIRED.CONDITIONAL", "This event counts mispredicted conditional branch instructions retired."},
    {"BR_MISP_RETIRED.CONDITIONAL_PS", "This is a precise version (that is, uses PEBS) of the event that counts mispredicted conditional branch instructions retired."},
    {"BR_MISP_RETIRED.NEAR_CALL", "Counts both taken and not taken retired mispredicted direct and indirect near calls, including both register and memory indirect."},
    {"BR_MISP_RETIRED.NEAR_CALL_PS", "This event counts both taken and not taken retired mispredicted direct and indirect near calls, including both register and memory indirect."},
    {"BR_MISP_RETIRED.NEAR_TAKEN", "Number of near branch instructions retired that were mispredicted and taken."},
    {"BR_MISP_RETIRED.NEAR_TAKEN_PS", "Number of near branch instructions retired that were mispredicted and taken."},
    {"CPU_CLK_THREAD_UNHALTED.ONE_THREAD_ACTIVE", "Core crystal clock cycles when this thread is unhalted and the other thread is halted."},
    {"CPU_CLK_THREAD_UNHALTED.REF_XCLK", "Core crystal clock cycles when the thread is unhalted."},
    {"CPU_CLK_THREAD_UNHALTED.REF_XCLK_ANY", "Core crystal clock cycles when at least one thread on the physical core is unhalted."},
    {"CPU_CLK_UNHALTED.ONE_THREAD_ACTIVE", "Core crystal clock cycles when this thread is unhalted and the other thread is halted."},
    {"CPU_CLK_UNHALTED.REF_TSC", "Counts the number of reference cycles when the core is not in a halt state. The core enters the halt state when it is running the HLT instruction or the MWAIT instruction. This event is not affected by core frequency changes (for example, P states, TM2 transitions) but has the same incrementing frequency as the time stamp counter. This event can approximate elapsed time while the core was not in a halt state. This event has a constant ratio with the CPU_CLK_UNHALTED.REF_XCLK event. It is counted on a dedicated fixed counter, leaving the four (eight when Hyperthreading is disabled) programmable counters available for other events. Note: On all current platforms this event stops counting during 'throttling (TM)' states duty off periods the processor is 'halted'. The counter update is done at a lower clock rate then the core clock the overflow status bit for this counter may appear 'sticky'. After the counter has overflowed and software clears the overflow status bit and resets the counter to less than MAX. The reset value to the counter is not clocked immediately so the overflow status bit will flip 'high (1)' and generate another PMI (if enabled) after which the reset value gets clocked into the counter. Therefore, software will get the interrupt, read the overflow status bit '1 for bit 34 while the counter value is less than MAX. Software should ignore this case."},
    {"CPU_CLK_UNHALTED.REF_XCLK", "Core crystal clock cycles when the thread is unhalted."},
    {"CPU_CLK_UNHALTED.REF_XCLK_ANY", "Core crystal clock cycles when at least one thread on the physical core is unhalted."},
    {"CPU_CLK_UNHALTED.RING0_TRANS", "Counts when the Current Privilege Level (CPL) transitions from ring 1, 2 or 3 to ring 0 (Kernel)."},
    {"CPU_CLK_UNHALTED.THREAD", "Counts the number of core cycles while the thread is not in a halt state. The thread enters the halt state when it is running the HLT instruction. This event is a component in many key event ratios. The core frequency may change from time to time due to transitions associated with Enhanced Intel SpeedStep Technology or TM2. For this reason this event may have a changing ratio with regards to time. When the core frequency is constant, this event can approximate elapsed time while the core was not in the halt state. It is counted on a dedicated fixed counter, leaving the four (eight when Hyperthreading is disabled) programmable counters available for other events."},
    {"CPU_CLK_UNHALTED.THREAD_ANY", "Core cycles when at least one thread on the physical core is not in halt state."},
    {"CPU_CLK_UNHALTED.THREAD_P", "This is an architectural event that counts the number of thread cycles while the thread is not in a halt state. The thread enters the halt state when it is running the HLT instruction. The core frequency may change from time to time due to power or thermal throttling. For this reason, this event may have a changing ratio with regards to wall clock time."},
    {"CPU_CLK_UNHALTED.THREAD_P_ANY", "Core cycles when at least one thread on the physical core is not in halt state."},
    {"CYCLE_ACTIVITY.CYCLES_L1D_MISS", "Cycles while L1 cache miss demand load is outstanding."},
    {"CYCLE_ACTIVITY.CYCLES_L2_MISS", "Cycles while L2 cache miss demand load is outstanding."},
    {"CYCLE_ACTIVITY.CYCLES_L3_MISS", "Cycles while L3 cache miss demand load is outstanding."},
    {"CYCLE_ACTIVITY.CYCLES_MEM_ANY", "Cycles while memory subsystem has an outstanding load."},
    {"CYCLE_ACTIVITY.STALLS_L1D_MISS", "Execution stalls while L1 cache miss demand load is outstanding."},
    {"CYCLE_ACTIVITY.STALLS_L2_MISS", "Execution stalls while L2 cache miss demand load is outstanding."},
    {"CYCLE_ACTIVITY.STALLS_L3_MISS", "Execution stalls while L3 cache miss demand load is outstanding."},
    {"CYCLE_ACTIVITY.STALLS_MEM_ANY", "Execution stalls while memory subsystem has an outstanding load."},
    {"CYCLE_ACTIVITY.STALLS_TOTAL", "Total execution stalls."},
    {"DSB2MITE_SWITCHES.PENALTY_CYCLES", "Counts Decode Stream Buffer (DSB)-to-MITE switch true penalty cycles. These cycles do not include uops routed through because of the switch itself, for example, when Instruction Decode Queue (IDQ) pre-allocation is unavailable, or Instruction Decode Queue (IDQ) is full. SBD-to-MITE switch true penalty cycles happen after the merge mux (MM) receives Decode Stream Buffer (DSB) Sync-indication until receiving the first MITE uop. MM is placed before Instruction Decode Queue (IDQ) to merge uops being fed from the MITE and Decode Stream Buffer (DSB) paths. Decode Stream Buffer (DSB) inserts the Sync-indication whenever a Decode Stream Buffer (DSB)-to-MITE switch occurs.Penalty: A Decode Stream Buffer (DSB) hit followed by a Decode Stream Buffer (DSB) miss can cost up to six cycles in which no uops are delivered to the IDQ. Most often, such switches from the Decode Stream Buffer (DSB) to the legacy pipeline cost 0–2 cycles."},
    {"DTLB_LOAD_MISSES.MISS_CAUSES_A_WALK", "Counts demand data loads that caused a page walk of any page size (4K/2M/4M/1G). This implies it missed in all TLB levels, but the walk need not have completed."},
    {"DTLB_LOAD_MISSES.STLB_HIT", "Counts loads that miss the DTLB (Data TLB) and hit the STLB (Second level TLB)."},
    {"DTLB_LOAD_MISSES.WALK_ACTIVE", "Counts cycles when at least one PMH (Page Miss Handler) is busy with a page walk for a load."},
    {"DTLB_LOAD_MISSES.WALK_COMPLETED", "Counts demand data loads that caused a completed page walk of any page size (4K/2M/4M/1G). This implies it missed in all TLB levels. The page walk can end with or without a fault."},
    {"DTLB_LOAD_MISSES.WALK_COMPLETED_1G", "Counts page walks completed due to demand data loads whose address translations missed in the TLB and were mapped to 4K pages. The page walks can end with or without a page fault."},
    {"DTLB_LOAD_MISSES.WALK_COMPLETED_2M_4M", "Counts page walks completed due to demand data loads whose address translations missed in the TLB and were mapped to 2M/4M pages. The page walks can end with or without a page fault."},
    {"DTLB_LOAD_MISSES.WALK_COMPLETED_4K", "Counts page walks completed due to demand data loads whose address translations missed in the TLB and were mapped to 4K pages. The page walks can end with or without a page fault."},
    {"DTLB_LOAD_MISSES.WALK_PENDING", "Counts 1 per cycle for each PMH that is busy with a page walk for a load. EPT page walk duration are excluded in Skylake microarchitecture."},
    {"DTLB_STORE_MISSES.MISS_CAUSES_A_WALK", "Counts demand data stores that caused a page walk of any page size (4K/2M/4M/1G). This implies it missed in all TLB levels, but the walk need not have completed."},
    {"DTLB_STORE_MISSES.STLB_HIT", "Stores that miss the DTLB (Data TLB) and hit the STLB (2nd Level TLB)."},
    {"DTLB_STORE_MISSES.WALK_ACTIVE", "Counts cycles when at least one PMH (Page Miss Handler) is busy with a page walk for a store."},
    {"DTLB_STORE_MISSES.WALK_COMPLETED", "Counts demand data stores that caused a completed page walk of any page size (4K/2M/4M/1G). This implies it missed in all TLB levels. The page walk can end with or without a fault."},
    {"DTLB_STORE_MISSES.WALK_COMPLETED_1G", "Counts page walks completed due to demand data stores whose address translations missed in the TLB and were mapped to 1G pages. The page walks can end with or without a page fault."},
    {"DTLB_STORE_MISSES.WALK_COMPLETED_2M_4M", "Counts page walks completed due to demand data stores whose address translations missed in the TLB and were mapped to 2M/4M pages. The page walks can end with or without a page fault."},
    {"DTLB_STORE_MISSES.WALK_COMPLETED_4K", "Counts page walks completed due to demand data stores whose address translations missed in the TLB and were mapped to 4K pages. The page walks can end with or without a page fault."},
    {"DTLB_STORE_MISSES.WALK_PENDING", "Counts 1 per cycle for each PMH that is busy with a page walk for a store. EPT page walk duration are excluded in Skylake microarchitecture."},
    {"EPT.WALK_PENDING", "Counts cycles for each PMH (Page Miss Handler) that is busy with an EPT (Extended Page Table) walk for any request type."},
    {"EXE_ACTIVITY.1_PORTS_UTIL", "Counts cycles during which a total of 1 uop was executed on all ports and Reservation Station (RS) was not empty."},
    {"EXE_ACTIVITY.2_PORTS_UTIL", "Counts cycles during which a total of 2 uops were executed on all ports and Reservation Station (RS) was not empty."},
    {"EXE_ACTIVITY.3_PORTS_UTIL", "Cycles total of 3 uops are executed on all ports and Reservation Station (RS) was not empty."},
    {"EXE_ACTIVITY.4_PORTS_UTIL", "Cycles total of 4 uops are executed on all ports and Reservation Station (RS) was not empty."},
    {"EXE_ACTIVITY.BOUND_ON_STORES", "Cycles where the Store Buffer was full and no outstanding load."},
    {"EXE_ACTIVITY.EXE_BOUND_0_PORTS", "Counts cycles during which no uops were executed on all ports and Reservation Station (RS) was not empty."},
    {"FP_ARITH_INST_RETIRED.128B_PACKED_DOUBLE", "Number of SSE/AVX computational 128-bit packed double precision floating-point instructions retired. Each count represents 2 computations. Applies to SSE* and AVX* packed double precision floating-point instructions: ADD SUB MUL DIV MIN MAX SQRT DPP FM(N)ADD/SUB. DPP and FM(N)ADD/SUB instructions count twice as they perform multiple calculations per element."},
    {"FP_ARITH_INST_RETIRED.128B_PACKED_SINGLE", "Number of SSE/AVX computational 128-bit packed single precision floating-point instructions retired. Each count represents 4 computations. Applies to SSE* and AVX* packed single precision floating-point instructions: ADD SUB MUL DIV MIN MAX RCP RSQRT SQRT DPP FM(N)ADD/SUB. DPP and FM(N)ADD/SUB instructions count twice as they perform multiple calculations per element."},
    {"FP_ARITH_INST_RETIRED.256B_PACKED_DOUBLE", "Number of SSE/AVX computational 256-bit packed double precision floating-point instructions retired. Each count represents 4 computations. Applies to SSE* and AVX* packed double precision floating-point instructions: ADD SUB MUL DIV MIN MAX SQRT DPP FM(N)ADD/SUB. DPP and FM(N)ADD/SUB instructions count twice as they perform multiple calculations per element."},
    {"FP_ARITH_INST_RETIRED.256B_PACKED_SINGLE", "Number of SSE/AVX computational 256-bit packed single precision floating-point instructions retired. Each count represents 8 computations. Applies to SSE* and AVX* packed single precision floating-point instructions: ADD SUB MUL DIV MIN MAX RCP RSQRT SQRT DPP FM(N)ADD/SUB. DPP and FM(N)ADD/SUB instructions count twice as they perform multiple calculations per element."},
    {"FP_ARITH_INST_RETIRED.SCALAR_DOUBLE", "Number of SSE/AVX computational scalar double precision floating-point instructions retired. Each count represents 1 computation. Applies to SSE* and AVX* scalar double precision floating-point instructions: ADD SUB MUL DIV MIN MAX SQRT FM(N)ADD/SUB. FM(N)ADD/SUB instructions count twice as they perform multiple calculations per element."},
    {"FP_ARITH_INST_RETIRED.SCALAR_SINGLE", "Number of SSE/AVX computational scalar single precision floating-point instructions retired. Each count represents 1 computation. Applies to SSE* and AVX* scalar single precision floating-point instructions: ADD SUB MUL DIV MIN MAX RCP RSQRT SQRT FM(N)ADD/SUB. FM(N)ADD/SUB instructions count twice as they perform multiple calculations per element."},
    {"FP_ASSIST.ANY", "Counts cycles with any input and output SSE or x87 FP assist. If an input and output assist are detected on the same cycle the event increments by 1."},
    {"FRONTEND_RETIRED.DSB_MISS", "Counts retired Instructions that experienced DSB (Decode stream buffer i.e. the decoded instruction-cache) miss."},
    {"FRONTEND_RETIRED.DSB_MISS_PS", "Counts retired Instructions that experienced DSB (Decode stream buffer i.e. the decoded instruction-cache) miss."},
    {"FRONTEND_RETIRED.ITLB_MISS", "Counts retired Instructions that experienced iTLB (Instruction TLB) true miss."},
    {"FRONTEND_RETIRED.ITLB_MISS_PS", "Counts retired Instructions that experienced iTLB (Instruction TLB) true miss."},
    {"FRONTEND_RETIRED.L1I_MISS", "Retired Instructions who experienced Instruction L1 Cache true miss."},
    {"FRONTEND_RETIRED.L1I_MISS_PS", "Retired Instructions who experienced Instruction L1 Cache true miss. Precise Event."},
    {"FRONTEND_RETIRED.L2_MISS", "Retired Instructions who experienced Instruction L2 Cache true miss."},
    {"FRONTEND_RETIRED.L2_MISS_PS", "Retired Instructions who experienced Instruction L2 Cache true miss. Precise Event."},
    {"FRONTEND_RETIRED.LATENCY_GE_128", "Retired instructions that are fetched after an interval where the front-end delivered no uops for a period of 128 cycles which was not interrupted by a back-end stall."},
    {"FRONTEND_RETIRED.LATENCY_GE_128_PS", "Retired instructions that are fetched after an interval where the front-end delivered no uops for a period of 128 cycles which was not interrupted by a back-end stall. Precise Event."},
    {"FRONTEND_RETIRED.LATENCY_GE_16", "Counts retired instructions that are delivered to the back-end after a front-end stall of at least 16 cycles. During this period the front-end delivered no uops."},
    {"FRONTEND_RETIRED.LATENCY_GE_16_PS", "Counts retired instructions that are delivered to the back-end after a front-end stall of at least 16 cycles. During this period the front-end delivered no uops."},
    {"FRONTEND_RETIRED.LATENCY_GE_2", "Retired instructions that are fetched after an interval where the front-end delivered no uops for a period of 2 cycles which was not interrupted by a back-end stall."},
    {"FRONTEND_RETIRED.LATENCY_GE_2_BUBBLES_GE_1", "Counts retired instructions that are delivered to the back-end after the front-end had at least 1 bubble-slot for a period of 2 cycles. A bubble-slot is an empty issue-pipeline slot while there was no RAT stall."},
    {"FRONTEND_RETIRED.LATENCY_GE_2_BUBBLES_GE_1_PS", "Counts retired instructions that are delivered to the back-end after the front-end had at least 1 bubble-slot for a period of 2 cycles. A bubble-slot is an empty issue-pipeline slot while there was no RAT stall."},
    {"FRONTEND_RETIRED.LATENCY_GE_2_BUBBLES_GE_2", "Retired instructions that are fetched after an interval where the front-end had at least 2 bubble-slots for a period of 2 cycles which was not interrupted by a back-end stall."},
    {"FRONTEND_RETIRED.LATENCY_GE_2_BUBBLES_GE_2_PS", "Retired instructions that are fetched after an interval where the front-end had at least 2 bubble-slots for a period of 2 cycles which was not interrupted by a back-end stall. Precise Event."},
    {"FRONTEND_RETIRED.LATENCY_GE_2_BUBBLES_GE_3", "Retired instructions that are fetched after an interval where the front-end had at least 3 bubble-slots for a period of 2 cycles which was not interrupted by a back-end stall."},
    {"FRONTEND_RETIRED.LATENCY_GE_2_BUBBLES_GE_3_PS", "Retired instructions that are fetched after an interval where the front-end had at least 3 bubble-slots for a period of 2 cycles which was not interrupted by a back-end stall. Precise Event."},
    {"FRONTEND_RETIRED.LATENCY_GE_2_PS", "Retired instructions that are fetched after an interval where the front-end delivered no uops for a period of 2 cycles which was not interrupted by a back-end stall. Precise Event."},
    {"FRONTEND_RETIRED.LATENCY_GE_256", "Retired instructions that are fetched after an interval where the front-end delivered no uops for a period of 256 cycles which was not interrupted by a back-end stall."},
    {"FRONTEND_RETIRED.LATENCY_GE_256_PS", "Retired instructions that are fetched after an interval where the front-end delivered no uops for a period of 256 cycles which was not interrupted by a back-end stall. Precise Event."},
    {"FRONTEND_RETIRED.LATENCY_GE_32", "Counts retired instructions that are delivered to the back-end after a front-end stall of at least 32 cycles. During this period the front-end delivered no uops."},
    {"FRONTEND_RETIRED.LATENCY_GE_32_PS", "Counts retired instructions that are delivered to the back-end after a front-end stall of at least 32 cycles. During this period the front-end delivered no uops."},
    {"FRONTEND_RETIRED.LATENCY_GE_4", "Retired instructions that are fetched after an interval where the front-end delivered no uops for a period of 4 cycles which was not interrupted by a back-end stall."},
    {"FRONTEND_RETIRED.LATENCY_GE_4_PS", "Retired instructions that are fetched after an interval where the front-end delivered no uops for a period of 4 cycles which was not interrupted by a back-end stall. Precise Event."},
    {"FRONTEND_RETIRED.LATENCY_GE_512", "Retired instructions that are fetched after an interval where the front-end delivered no uops for a period of 512 cycles which was not interrupted by a back-end stall."},
    {"FRONTEND_RETIRED.LATENCY_GE_512_PS", "Retired instructions that are fetched after an interval where the front-end delivered no uops for a period of 512 cycles which was not interrupted by a back-end stall. Precise Event."},
    {"FRONTEND_RETIRED.LATENCY_GE_64", "Retired instructions that are fetched after an interval where the front-end delivered no uops for a period of 64 cycles which was not interrupted by a back-end stall."},
    {"FRONTEND_RETIRED.LATENCY_GE_64_PS", "Retired instructions that are fetched after an interval where the front-end delivered no uops for a period of 64 cycles which was not interrupted by a back-end stall. Precise Event."},
    {"FRONTEND_RETIRED.LATENCY_GE_8", "Counts retired instructions that are delivered to the back-end after a front-end stall of at least 8 cycles. During this period the front-end delivered no uops."},
    {"FRONTEND_RETIRED.LATENCY_GE_8_PS", "Counts retired instructions that are delivered to the back-end after a front-end stall of at least 8 cycles. During this period the front-end delivered no uops."},
    {"FRONTEND_RETIRED.STLB_MISS", "Counts retired Instructions that experienced STLB (2nd level TLB) true miss."},
    {"FRONTEND_RETIRED.STLB_MISS_PS", "Counts retired Instructions that experienced STLB (2nd level TLB) true miss."},
    {"HLE_RETIRED.ABORTED", "Number of times HLE abort was triggered."},
    {"HLE_RETIRED.ABORTED_EVENTS", "Number of times an HLE execution aborted due to unfriendly events (such as interrupts)."},
    {"HLE_RETIRED.ABORTED_MEM", "Number of times an HLE execution aborted due to various memory events (e.g., read/write capacity and conflicts)."},
    {"HLE_RETIRED.ABORTED_MEMTYPE", "Number of times an HLE execution aborted due to incompatible memory type."},
    {"HLE_RETIRED.ABORTED_PS", "Number of times HLE abort was triggered. (PEBS)"},
    {"HLE_RETIRED.ABORTED_TIMER", "Number of times an HLE execution aborted due to hardware timer expiration."},
    {"HLE_RETIRED.ABORTED_UNFRIENDLY", "Number of times an HLE execution aborted due to HLE-unfriendly instructions and certain unfriendly events (such as AD assists etc.)."},
    {"HLE_RETIRED.COMMIT", "Number of times HLE commit succeeded."},
    {"HLE_RETIRED.START", "Number of times we entered an HLE region. Does not count nested transactions."},
    {"HW_INTERRUPTS.RECEIVED", "Counts the number of hardware interruptions received by the processor."},
    {"ICACHE_16B.IFDATA_STALL", "Cycles where a code line fetch is stalled due to an L1 instruction cache miss. The legacy decode pipeline works at a 16 Byte granularity."},
    {"ICACHE_64B.IFTAG_HIT", "Instruction fetch tag lookups that hit in the instruction cache (L1I). Counts at 64-byte cache-line granularity."},
    {"ICACHE_64B.IFTAG_MISS", "Instruction fetch tag lookups that miss in the instruction cache (L1I). Counts at 64-byte cache-line granularity."},
    {"ICACHE_64B.IFTAG_STALL", "Cycles where a code fetch is stalled due to L1 instruction cache tag miss."},
    {"IDQ.ALL_DSB_CYCLES_4_UOPS", "Counts the number of cycles 4 uops were delivered to Instruction Decode Queue (IDQ) from the Decode Stream Buffer (DSB) path. Count includes uops that may 'bypass' the IDQ."},
    {"IDQ.ALL_DSB_CYCLES_ANY_UOPS", "Counts the number of cycles uops were delivered to Instruction Decode Queue (IDQ) from the Decode Stream Buffer (DSB) path. Count includes uops that may 'bypass' the IDQ."},
    {"IDQ.ALL_MITE_CYCLES_4_UOPS", "Counts the number of cycles 4 uops were delivered to the Instruction Decode Queue (IDQ) from the MITE (legacy decode pipeline) path. Counting includes uops that may 'bypass' the IDQ. During these cycles uops are not being delivered from the Decode Stream Buffer (DSB)."},
    {"IDQ.ALL_MITE_CYCLES_ANY_UOPS", "Counts the number of cycles uops were delivered to the Instruction Decode Queue (IDQ) from the MITE (legacy decode pipeline) path. Counting includes uops that may 'bypass' the IDQ. During these cycles uops are not being delivered from the Decode Stream Buffer (DSB)."},
    {"IDQ.DSB_CYCLES", "Counts cycles during which uops are being delivered to Instruction Decode Queue (IDQ) from the Decode Stream Buffer (DSB) path. Counting includes uops that may 'bypass' the IDQ."},
    {"IDQ.DSB_UOPS", "Counts the number of uops delivered to Instruction Decode Queue (IDQ) from the Decode Stream Buffer (DSB) path. Counting includes uops that may 'bypass' the IDQ."},
    {"IDQ.MITE_CYCLES", "Counts cycles during which uops are being delivered to Instruction Decode Queue (IDQ) from the MITE path. Counting includes uops that may 'bypass' the IDQ."},
    {"IDQ.MITE_UOPS", "Counts the number of uops delivered to Instruction Decode Queue (IDQ) from the MITE path. Counting includes uops that may 'bypass' the IDQ. This also means that uops are not being delivered from the Decode Stream Buffer (DSB)."},
    {"IDQ.MS_CYCLES", "Counts cycles during which uops are being delivered to Instruction Decode Queue (IDQ) while the Microcode Sequencer (MS) is busy. Counting includes uops that may 'bypass' the IDQ. Uops maybe initiated by Decode Stream Buffer (DSB) or MITE."},
    {"IDQ.MS_DSB_CYCLES", "Counts cycles during which uops initiated by Decode Stream Buffer (DSB) are being delivered to Instruction Decode Queue (IDQ) while the Microcode Sequencer (MS) is busy. Counting includes uops that may 'bypass' the IDQ."},
    {"IDQ.MS_MITE_UOPS", "Counts the number of uops initiated by MITE and delivered to Instruction Decode Queue (IDQ) while the Microcode Sequencer (MS) is busy. Counting includes uops that may 'bypass' the IDQ."},
    {"IDQ.MS_SWITCHES", "Number of switches from DSB (Decode Stream Buffer) or MITE (legacy decode pipeline) to the Microcode Sequencer."},
    {"IDQ.MS_UOPS", "Counts the total number of uops delivered by the Microcode Sequencer (MS). Any instruction over 4 uops will be delivered by the MS. Some instructions such as transcendentals may additionally generate uops from the MS."},
    {"IDQ_UOPS_NOT_DELIVERED.CORE", "Counts the number of uops not delivered to Resource Allocation Table (RAT) per thread adding 4x when Resource Allocation Table (RAT) is not stalled and Instruction Decode Queue (IDQ) delivers x uops to Resource Allocation Table (RAT) (where x belongs to {0,1,2,3}). Counting does not cover cases when: a. IDQ-Resource Allocation Table (RAT) pipe serves the other thread. b. Resource Allocation Table (RAT) is stalled for the thread (including uop drops and clear BE conditions). c. Instruction Decode Queue (IDQ) delivers four uops."},
    {"IDQ_UOPS_NOT_DELIVERED.CYCLES_0_UOPS_DELIV.CORE", "Counts, on the per-thread basis, cycles when no uops are delivered to Resource Allocation Table (RAT). IDQ_Uops_Not_Delivered.core =4."},
    {"IDQ_UOPS_NOT_DELIVERED.CYCLES_FE_WAS_OK", "Counts cycles FE delivered 4 uops or Resource Allocation Table (RAT) was stalling FE."},
    {"IDQ_UOPS_NOT_DELIVERED.CYCLES_LE_1_UOP_DELIV.CORE", "Counts, on the per-thread basis, cycles when less than 1 uop is delivered to Resource Allocation Table (RAT). IDQ_Uops_Not_Delivered.core >= 3."},
    {"IDQ_UOPS_NOT_DELIVERED.CYCLES_LE_2_UOP_DELIV.CORE", "Cycles with less than 2 uops delivered by the front-end."},
    {"IDQ_UOPS_NOT_DELIVERED.CYCLES_LE_3_UOP_DELIV.CORE", "Cycles with less than 3 uops delivered by the front-end."},
    {"ILD_STALL.LCP", "Counts cycles that the Instruction Length decoder (ILD) stalls occurred due to dynamically changing prefix length of the decoded instruction (by operand size prefix instruction 0x66, address size prefix instruction 0x67 or REX.W for Intel64). Count is proportional to the number of prefixes in a 16B-line. This may result in a three-cycle penalty for each LCP (Length changing prefix) in a 16-byte chunk."},
    {"INST_RETIRED.ANY", "Counts the number of instructions retired from execution. For instructions that consist of multiple micro-ops, Counts the retirement of the last micro-op of the instruction. Counting continues during hardware interrupts, traps, and inside interrupt handlers. Notes: INST_RETIRED.ANY is counted by a designated fixed counter, leaving the four (eight when Hyperthreading is disabled) programmable counters available for other events. INST_RETIRED.ANY_P is counted by a programmable counter and it is an architectural performance event. Counting: Faulting executions of GETSEC/VM entry/VM Exit/MWait will not count as retired instructions."},
    {"INST_RETIRED.ANY_P", "Counts the number of instructions (EOMs) retired. Counting covers macro-fused instructions individually (that is, increments by two)."},
    {"INST_RETIRED.PREC_DIST", "A version of INST_RETIRED that allows for a more unbiased distribution of samples across instructions retired. It utilizes the Precise Distribution of Instructions Retired (PDIR) feature to mitigate some bias in how retired instructions get sampled."},
    {"INST_RETIRED.TOTAL_CYCLES_PS", "Number of cycles using an always true condition applied to PEBS instructions retired event. (inst_ret< 16)"},
    {"INT_MISC.CLEAR_RESTEER_CYCLES", "Cycles the issue-stage is waiting for front-end to fetch from resteered path following branch misprediction or machine clear events."},
    {"INT_MISC.RECOVERY_CYCLES", "Core cycles the Resource allocator was stalled due to recovery from an earlier branch misprediction or machine clear event."},
    {"INT_MISC.RECOVERY_CYCLES_ANY", "Core cycles the allocator was stalled due to recovery from earlier clear event for any thread running on the physical core (e.g. misprediction or memory nuke)."},
    {"ITLB.ITLB_FLUSH", "Counts the number of flushes of the big or small ITLB pages. Counting include both TLB Flush (covering all sets) and TLB Set Clear (set-specific)."},
    {"ITLB_MISSES.MISS_CAUSES_A_WALK", "Counts page walks of any page size (4K/2M/4M/1G) caused by a code fetch. This implies it missed in the ITLB and further levels of TLB, but the walk need not have completed."},
    {"ITLB_MISSES.STLB_HIT", "Instruction fetch requests that miss the ITLB and hit the STLB."},
    {"ITLB_MISSES.WALK_ACTIVE", "Cycles when at least one PMH is busy with a page walk for code (instruction fetch) request. EPT page walk duration are excluded in Skylake microarchitecture."},
    {"ITLB_MISSES.WALK_COMPLETED", "Counts completed page walks (2M and 4M page sizes) caused by a code fetch. This implies it missed in the ITLB and further levels of TLB. The page walk can end with or without a fault."},
    {"ITLB_MISSES.WALK_COMPLETED_1G", "Counts store misses in all DTLB levels that cause a completed page walk (1G page size). The page walk can end with or without a fault."},
    {"ITLB_MISSES.WALK_COMPLETED_2M_4M", "Counts code misses in all ITLB levels that caused a completed page walk (2M and 4M page sizes). The page walk can end with or without a fault."},
    {"ITLB_MISSES.WALK_COMPLETED_4K", "Counts completed page walks (4K page size) caused by a code fetch. This implies it missed in the ITLB and further levels of TLB. The page walk can end with or without a fault."},
    {"ITLB_MISSES.WALK_PENDING", "Counts 1 per cycle for each PMH (Page Miss Handler) that is busy with a page walk for an instruction fetch request. EPT page walk duration are excluded in Skylake michroarchitecture."},
    {"L1D.REPLACEMENT", "Counts L1D data line replacements including opportunistic replacements, and replacements that require stall-for-replace or block-for-replace."},
    {"L1D_PEND_MISS.FB_FULL", "Number of times a request needed a FB (Fill Buffer) entry but there was no entry available for it. A request includes cacheable/uncacheable demands that are load, store or SW prefetch instructions."},
    {"L1D_PEND_MISS.PENDING", "Counts duration of L1D miss outstanding, that is each cycle number of Fill Buffers (FB) outstanding required by Demand Reads. FB either is held by demand loads, or it is held by non-demand loads and gets hit at least once by demand. The valid outstanding interval is defined until the FB deallocation by one of the following ways: from FB allocation, if FB is allocated by demand from the demand Hit FB, if it is allocated by hardware or software prefetch.Note: In the L1D, a Demand Read contains cacheable or noncacheable demand loads, including ones causing cache-line splits and reads due to page walks resulted from any request type."},
    {"L1D_PEND_MISS.PENDING_CYCLES", "Counts duration of L1D miss outstanding in cycles."},
    {"L1D_PEND_MISS.PENDING_CYCLES_ANY", "Cycles with L1D load Misses outstanding from any thread on physical core."},
    {"L2_LINES_IN.ALL", "Counts the number of L2 cache lines filling the L2. Counting does not cover rejects."},
    {"L2_LINES_OUT.NON_SILENT", "Counts the number of lines that are evicted by L2 cache when triggered by an L2 cache fill. Those lines are in Modified state. Modified lines are written back to L3"},
    {"L2_LINES_OUT.SILENT", "Counts the number of lines that are silently dropped by L2 cache when triggered by an L2 cache fill. These lines are typically in Shared or Exclusive state. A non-threaded event."},
    {"L2_LINES_OUT.USELESS_HWPF", "Counts the number of lines that have been hardware prefetched but not used and now evicted by L2 cache"},
    {"L2_LINES_OUT.USELESS_PREF", "Counts the number of lines that have been hardware prefetched but not used and now evicted by L2 cache."},
    {"L2_RQSTS.ALL_CODE_RD", "Counts the total number of L2 code requests."},
    {"L2_RQSTS.ALL_DEMAND_DATA_RD", "Counts the number of demand Data Read requests (including requests from L1D hardware prefetchers). These loads may hit or miss L2 cache. Only non rejected loads are counted."},
    {"L2_RQSTS.ALL_DEMAND_MISS", "Demand requests that miss L2 cache."},
    {"L2_RQSTS.ALL_DEMAND_REFERENCES", "Demand requests to L2 cache."},
    {"L2_RQSTS.ALL_PF", "Counts the total number of requests from the L2 hardware prefetchers."},
    {"L2_RQSTS.ALL_RFO", "Counts the total number of RFO (read for ownership) requests to L2 cache. L2 RFO requests include both L1D demand RFO misses as well as L1D RFO prefetches."},
    {"L2_RQSTS.CODE_RD_HIT", "Counts L2 cache hits when fetching instructions, code reads."},
    {"L2_RQSTS.CODE_RD_MISS", "Counts L2 cache misses when fetching instructions."},
    {"L2_RQSTS.DEMAND_DATA_RD_HIT", "Counts the number of demand Data Read requests that hit L2 cache. Only non rejected loads are counted."},
    {"L2_RQSTS.DEMAND_DATA_RD_MISS", "Counts the number of demand Data Read requests that miss L2 cache. Only not rejected loads are counted."},
    {"L2_RQSTS.MISS", "All requests that miss L2 cache."},
    {"L2_RQSTS.PF_HIT", "Counts requests from the L1/L2/L3 hardware prefetchers or Load software prefetches that hit L2 cache."},
    {"L2_RQSTS.PF_MISS", "Counts requests from the L1/L2/L3 hardware prefetchers or Load software prefetches that miss L2 cache."},
    {"L2_RQSTS.REFERENCES", "All L2 requests."},
    {"L2_RQSTS.RFO_HIT", "Counts the RFO (Read-for-Ownership) requests that hit L2 cache."},
    {"L2_RQSTS.RFO_MISS", "Counts the RFO (Read-for-Ownership) requests that miss L2 cache."},
    {"L2_TRANS.L2_WB", "Counts L2 writebacks that access L2 cache."},
    {"LD_BLOCKS.NO_SR", "The number of times that split load operations are temporarily blocked because all resources for handling the split accesses are in use."},
    {"LD_BLOCKS.STORE_FORWARD", "Counts how many times the load operation got the true Block-on-Store blocking code preventing store forwarding. This includes cases when:a. preceding store conflicts with the load (incomplete overlap),b. store forwarding is impossible due to u-arch limitations,c. preceding lock RMW operations are not forwarded,d. store has the no-forward bit set (uncacheable/page-split/masked stores),e. all-blocking stores are used (mostly, fences and port I/O), and others.The most common case is a load blocked due to its address range overlapping with a preceding smaller uncompleted store. Note: This event does not take into account cases of out-of-SW-control (for example, SbTailHit), unknown physical STA, and cases of blocking loads on store due to being non-WB memory type or a lock. These cases are covered by other events. See the table of not supported store forwards in the Optimization Guide."},
    {"LD_BLOCKS_PARTIAL.ADDRESS_ALIAS", "Counts false dependencies in MOB when the partial comparison upon loose net check and dependency was resolved by the Enhanced Loose net mechanism. This may not result in high performance penalties. Loose net checks can fail when loads and stores are 4k aliased."},
    {"LOAD_HIT_PRE.SW_PF", "Counts all not software-prefetch load dispatches that hit the fill buffer (FB) allocated for the software prefetch. It can also be incremented by some lock instructions. So it should only be used with profiling so that the locks can be excluded by ASM (Assembly File) inspection of the nearby instructions."},
    {"LONGEST_LAT_CACHE.MISS", "Counts core-originated cacheable requests that miss the L3 cache (Longest Latency cache). Requests include data and code reads, Reads-for-Ownership (RFOs), speculative accesses and hardware prefetches from L1 and L2. It does not include all misses to the L3."},
    {"LONGEST_LAT_CACHE.REFERENCE", "Counts core-originated cacheable requests to the L3 cache (Longest Latency cache). Requests include data and code reads, Reads-for-Ownership (RFOs), speculative accesses and hardware prefetches from L1 and L2. It does not include all accesses to the L3."},
    {"LSD.CYCLES_4_UOPS", "Counts the cycles when 4 uops are delivered by the LSD (Loop-stream detector)."},
    {"LSD.CYCLES_ACTIVE", "Counts the cycles when at least one uop is delivered by the LSD (Loop-stream detector)."},
    {"LSD.UOPS", "Number of uops delivered to the back-end by the LSD(Loop Stream Detector)."},
    {"MACHINE_CLEARS.COUNT", "Number of machine clears (nukes) of any type."},
    {"MACHINE_CLEARS.MEMORY_ORDERING", "Counts the number of memory ordering Machine Clears detected. Memory Ordering Machine Clears can result from one of the following:a. memory disambiguation,b. external snoop, orc. cross SMT-HW-thread snoop (stores) hitting load buffer."},
    {"MACHINE_CLEARS.SMC", "Counts self-modifying code (SMC) detected, which causes a machine clear."},
    {"MEM_INST_RETIRED.ALL_LOADS", "All retired load instructions."},
    {"MEM_INST_RETIRED.ALL_LOADS_PS", "All retired load instructions. (Precise Event)"},
    {"MEM_INST_RETIRED.ALL_STORES", "All retired store instructions."},
    {"MEM_INST_RETIRED.ALL_STORES_PS", "All retired store instructions."},
    {"MEM_INST_RETIRED.LOCK_LOADS", "Retired load instructions with locked access."},
    {"MEM_INST_RETIRED.LOCK_LOADS_PS", "Retired load instructions with locked access. (Precise Event)"},
    {"MEM_INST_RETIRED.SPLIT_LOADS", "Counts retired load instructions that split across a cacheline boundary."},
    {"MEM_INST_RETIRED.SPLIT_LOADS_PS", "Retired load instructions that split across a cacheline boundary. (Precise Event)"},
    {"MEM_INST_RETIRED.SPLIT_STORES", "Counts retired store instructions that split across a cacheline boundary."},
    {"MEM_INST_RETIRED.SPLIT_STORES_PS", "Retired store instructions that split across a cacheline boundary. (Precise Event)"},
    {"MEM_INST_RETIRED.STLB_MISS_LOADS", "Retired load instructions that miss the STLB."},
    {"MEM_INST_RETIRED.STLB_MISS_LOADS_PS", "Retired load instructions that miss the STLB."},
    {"MEM_INST_RETIRED.STLB_MISS_STORES", "Retired store instructions that miss the STLB."},
    {"MEM_INST_RETIRED.STLB_MISS_STORES_PS", "Retired store instructions that miss the STLB."},
    {"MEM_LOAD_L3_HIT_RETIRED.XSNP_HIT", "Retired load instructions which data sources were L3 and cross-core snoop hits in on-pkg core cache."},
    {"MEM_LOAD_L3_HIT_RETIRED.XSNP_HIT_PS", "Retired load instructions which data sources were L3 and cross-core snoop hits in on-pkg core cache."},
    {"MEM_LOAD_L3_HIT_RETIRED.XSNP_HITM", "Retired load instructions which data sources were HitM responses from shared L3."},
    {"MEM_LOAD_L3_HIT_RETIRED.XSNP_HITM_PS", "Retired load instructions which data sources were HitM responses from shared L3."},
    {"MEM_LOAD_L3_HIT_RETIRED.XSNP_MISS", "Retired load instructions which data sources were L3 hit and cross-core snoop missed in on-pkg core cache."},
    {"MEM_LOAD_L3_HIT_RETIRED.XSNP_MISS_PS", "Retired load instructions which data sources were L3 hit and cross-core snoop missed in on-pkg core cache."},
    {"MEM_LOAD_L3_HIT_RETIRED.XSNP_NONE", "Retired load instructions which data sources were hits in L3 without snoops required."},
    {"MEM_LOAD_L3_HIT_RETIRED.XSNP_NONE_PS", "Retired load instructions which data sources were hits in L3 without snoops required."},
    {"MEM_LOAD_MISC_RETIRED.UC", "Retired instructions with at least 1 uncacheable load or lock."},
    {"MEM_LOAD_MISC_RETIRED.UC_PS", "Retired instructions with at least 1 uncacheable load or lock."},
    {"MEM_LOAD_RETIRED.FB_HIT", "Counts retired load instructions with at least one uop was load missed in L1 but hit FB (Fill Buffers) due to preceding miss to the same cache line with data not ready."},
    {"MEM_LOAD_RETIRED.FB_HIT_PS", "Counts retired load instructions with at least one uop was load missed in L1 but hit FB (Fill Buffers) due to preceding miss to the same cache line with data not ready."},
    {"MEM_LOAD_RETIRED.L1_HIT", "Counts retired load instructions with at least one uop that hit in the L1 data cache. This event includes all SW prefetches and lock instructions regardless of the data source."},
    {"MEM_LOAD_RETIRED.L1_HIT_PS", "Counts retired load instructions with at least one uop that hit in the L1 data cache. This event includes all SW prefetches and lock instructions regardless of the data source."},
    {"MEM_LOAD_RETIRED.L1_MISS", "Counts retired load instructions with at least one uop that missed in the L1 cache."},
    {"MEM_LOAD_RETIRED.L1_MISS_PS", "Counts retired load instructions with at least one uop that missed in the L1 cache."},
    {"MEM_LOAD_RETIRED.L2_HIT", "Retired load instructions with L2 cache hits as data sources."},
    {"MEM_LOAD_RETIRED.L2_HIT_PS", "Retired load instructions with L2 cache hits as data sources."},
    {"MEM_LOAD_RETIRED.L2_MISS", "Retired load instructions missed L2 cache as data sources."},
    {"MEM_LOAD_RETIRED.L2_MISS_PS", "Retired load instructions missed L2 cache as data sources."},
    {"MEM_LOAD_RETIRED.L3_HIT", "Counts retired load instructions with at least one uop that hit in the L3 cache."},
    {"MEM_LOAD_RETIRED.L3_HIT_PS", "Retired load instructions with L3 cache hits as data sources."},
    {"MEM_LOAD_RETIRED.L3_MISS", "Counts retired load instructions with at least one uop that missed in the L3 cache."},
    {"MEM_LOAD_RETIRED.L3_MISS_PS", "Retired load instructions missed L3 cache as data sources."},
    {"MEM_TRANS_RETIRED.LOAD_LATENCY_GT_128", "Counts loads when the latency from first dispatch to completion is greater than 128 cycles. Reported latency may be longer than just the memory latency."},
    {"MEM_TRANS_RETIRED.LOAD_LATENCY_GT_16", "Counts loads when the latency from first dispatch to completion is greater than 16 cycles. Reported latency may be longer than just the memory latency."},
    {"MEM_TRANS_RETIRED.LOAD_LATENCY_GT_256", "Counts loads when the latency from first dispatch to completion is greater than 256 cycles. Reported latency may be longer than just the memory latency."},
    {"MEM_TRANS_RETIRED.LOAD_LATENCY_GT_32", "Counts loads when the latency from first dispatch to completion is greater than 32 cycles. Reported latency may be longer than just the memory latency."},
    {"MEM_TRANS_RETIRED.LOAD_LATENCY_GT_4", "Counts loads when the latency from first dispatch to completion is greater than 4 cycles. Reported latency may be longer than just the memory latency."},
    {"MEM_TRANS_RETIRED.LOAD_LATENCY_GT_512", "Counts loads when the latency from first dispatch to completion is greater than 512 cycles. Reported latency may be longer than just the memory latency."},
    {"MEM_TRANS_RETIRED.LOAD_LATENCY_GT_64", "Counts loads when the latency from first dispatch to completion is greater than 64 cycles. Reported latency may be longer than just the memory latency."},
    {"MEM_TRANS_RETIRED.LOAD_LATENCY_GT_8", "Counts loads when the latency from first dispatch to completion is greater than 8 cycles. Reported latency may be longer than just the memory latency."},
    {"OFFCORE_REQUESTS.ALL_DATA_RD", "Counts the demand and prefetch data reads. All Core Data Reads include cacheable 'Demands' and L2 prefetchers (not L3 prefetchers). Counting also covers reads due to page walks resulted from any request type."},
    {"OFFCORE_REQUESTS.ALL_REQUESTS", "Counts memory transactions reached the super queue including requests initiated by the core, all L3 prefetches, page walks, etc.."},
    {"OFFCORE_REQUESTS.DEMAND_CODE_RD", "Counts both cacheable and non-cacheable code read requests."},
    {"OFFCORE_REQUESTS.DEMAND_DATA_RD", "Counts the Demand Data Read requests sent to uncore. Use it in conjunction with OFFCORE_REQUESTS_OUTSTANDING to determine average latency in the uncore."},
    {"OFFCORE_REQUESTS.DEMAND_RFO", "Counts the demand RFO (read for ownership) requests including regular RFOs, locks, ItoM."},
    {"OFFCORE_REQUESTS.L3_MISS_DEMAND_DATA_RD", "Demand Data Read requests who miss L3 cache."},
    {"OFFCORE_REQUESTS_BUFFER.SQ_FULL", "Counts the number of cases when the offcore requests buffer cannot take more entries for the core. This can happen when the superqueue does not contain eligible entries, or when L1D writeback pending FIFO requests is full.Note: Writeback pending FIFO has six entries."},
    {"OFFCORE_REQUESTS_OUTSTANDING.ALL_DATA_RD", "Counts the number of offcore outstanding cacheable Core Data Read transactions in the super queue every cycle. A transaction is considered to be in the Offcore outstanding state between L2 miss and transaction completion sent to requestor (SQ de-allocation). See corresponding Umask under OFFCORE_REQUESTS."},
    {"OFFCORE_REQUESTS_OUTSTANDING.CYCLES_WITH_DATA_RD", "Counts cycles when offcore outstanding cacheable Core Data Read transactions are present in the super queue. A transaction is considered to be in the Offcore outstanding state between L2 miss and transaction completion sent to requestor (SQ de-allocation). See corresponding Umask under OFFCORE_REQUESTS."},
    {"OFFCORE_REQUESTS_OUTSTANDING.CYCLES_WITH_DEMAND_CODE_RD", "Counts the number of offcore outstanding Code Reads transactions in the super queue every cycle. The 'Offcore outstanding' state of the transaction lasts from the L2 miss until the sending transaction completion to requestor (SQ deallocation). See the corresponding Umask under OFFCORE_REQUESTS."},
    {"OFFCORE_REQUESTS_OUTSTANDING.CYCLES_WITH_DEMAND_DATA_RD", "Counts cycles when offcore outstanding Demand Data Read transactions are present in the super queue (SQ). A transaction is considered to be in the Offcore outstanding state between L2 miss and transaction completion sent to requestor (SQ de-allocation)."},
    {"OFFCORE_REQUESTS_OUTSTANDING.CYCLES_WITH_DEMAND_RFO", "Counts the number of offcore outstanding demand rfo Reads transactions in the super queue every cycle. The 'Offcore outstanding' state of the transaction lasts from the L2 miss until the sending transaction completion to requestor (SQ deallocation). See the corresponding Umask under OFFCORE_REQUESTS."},
    {"OFFCORE_REQUESTS_OUTSTANDING.CYCLES_WITH_L3_MISS_DEMAND_DATA_RD", "Cycles with at least 1 Demand Data Read requests who miss L3 cache in the superQ."},
    {"OFFCORE_REQUESTS_OUTSTANDING.DEMAND_CODE_RD", "Counts the number of offcore outstanding Code Reads transactions in the super queue every cycle. The 'Offcore outstanding' state of the transaction lasts from the L2 miss until the sending transaction completion to requestor (SQ deallocation). See the corresponding Umask under OFFCORE_REQUESTS."},
    {"OFFCORE_REQUESTS_OUTSTANDING.DEMAND_DATA_RD", "Counts the number of offcore outstanding Demand Data Read transactions in the super queue (SQ) every cycle. A transaction is considered to be in the Offcore outstanding state between L2 miss and transaction completion sent to requestor. See the corresponding Umask under OFFCORE_REQUESTS.Note: A prefetch promoted to Demand is counted from the promotion point."},
    {"OFFCORE_REQUESTS_OUTSTANDING.DEMAND_DATA_RD_GE_6", "Cycles with at least 6 offcore outstanding Demand Data Read transactions in uncore queue."},
    {"OFFCORE_REQUESTS_OUTSTANDING.DEMAND_RFO", "Counts the number of offcore outstanding RFO (store) transactions in the super queue (SQ) every cycle. A transaction is considered to be in the Offcore outstanding state between L2 miss and transaction completion sent to requestor (SQ de-allocation). See corresponding Umask under OFFCORE_REQUESTS."},
    {"OFFCORE_REQUESTS_OUTSTANDING.L3_MISS_DEMAND_DATA_RD", "Counts number of Offcore outstanding Demand Data Read requests that miss L3 cache in the superQ every cycle."},
    {"OFFCORE_REQUESTS_OUTSTANDING.L3_MISS_DEMAND_DATA_RD_GE_6", "Cycles with at least 6 Demand Data Read requests that miss L3 cache in the superQ."},
    {"OFFCORE_RESPONSE", "Offcore response can be programmed only with a specific pair of event select and counter MSR, and with specific event codes and predefine mask bit value in a dedicated MSR to specify attributes of the offcore transaction."},
    {"OTHER_ASSISTS.ANY", "Number of times a microcode assist is invoked by HW other than FP-assist. Examples include AD (page Access Dirty) and AVX* related assists."},
    {"RESOURCE_STALLS.ANY", "Counts resource-related stall cycles. Reasons for stalls can be as follows:a. *any* u-arch structure got full (LB, SB, RS, ROB, BOB, LM, Physical Register Reclaim Table (PRRT), or Physical History Table (PHT) slots).b. *any* u-arch structure got empty (like INT/SIMD FreeLists).c. FPU control word (FPCW), MXCSR.and others. This counts cycles that the pipeline back-end blocked uop delivery from the front-end."},
    {"RESOURCE_STALLS.SB", "Counts allocation stall cycles caused by the store buffer (SB) being full. This counts cycles that the pipeline back-end blocked uop delivery from the front-end."},
    {"ROB_MISC_EVENTS.LBR_INSERTS", "Increments when an entry is added to the Last Branch Record (LBR) array (or removed from the array in case of RETURNs in call stack mode). The event requires LBR enable via IA32_DEBUGCTL MSR and branch type selection via MSR_LBR_SELECT."},
    {"RS_EVENTS.EMPTY_CYCLES", "Counts cycles during which the reservation station (RS) is empty for the thread.; Note: In ST-mode, not active thread should drive 0. This is usually caused by severely costly branch mispredictions, or allocator/FE issues."},
    {"RS_EVENTS.EMPTY_END", "Counts end of periods where the Reservation Station (RS) was empty. Could be useful to precisely locate front-end Latency Bound issues."},
    {"RTM_RETIRED.ABORTED", "Number of times RTM abort was triggered."},
    {"RTM_RETIRED.ABORTED_EVENTS", "Number of times an RTM execution aborted due to none of the previous 4 categories (e.g. interrupt)."},
    {"RTM_RETIRED.ABORTED_MEM", "Number of times an RTM execution aborted due to various memory events (e.g. read/write capacity and conflicts)."},
    {"RTM_RETIRED.ABORTED_MEMTYPE", "Number of times an RTM execution aborted due to incompatible memory type."},
    {"RTM_RETIRED.ABORTED_PS", "Number of times RTM abort was triggered. (PEBS)"},
    {"RTM_RETIRED.ABORTED_TIMER", "Number of times an RTM execution aborted due to uncommon conditions."},
    {"RTM_RETIRED.ABORTED_UNFRIENDLY", "Number of times an RTM execution aborted due to HLE-unfriendly instructions."},
    {"RTM_RETIRED.COMMIT", "Number of times RTM commit succeeded."},
    {"RTM_RETIRED.START", "Number of times we entered an RTM region. Does not count nested transactions."},
    {"SQ_MISC.SPLIT_LOCK", "Counts the number of cache line split locks sent to the uncore."},
    {"SW_PREFETCH_ACCESS.NTA", "Number of PREFETCHNTA instructions executed."},
    {"SW_PREFETCH_ACCESS.PREFETCHW", "Number of PREFETCHW instructions executed."},
    {"SW_PREFETCH_ACCESS.T0", "Number of PREFETCHT0 instructions executed."},
    {"SW_PREFETCH_ACCESS.T1_T2", "Number of PREFETCHT1 or PREFETCHT2 instructions executed."},
    {"TLB_FLUSH.DTLB_THREAD", "Counts the number of DTLB flush attempts of the thread-specific entries."},
    {"TLB_FLUSH.STLB_ANY", "Counts the number of any STLB flush attempts (such as entire, VPID, PCID, InvPage, CR3 write, etc.)."},
    {"TX_EXEC.MISC1", "Counts the number of times a class of instructions that may cause a transactional abort was executed. Since this is the count of execution, it may not always cause a transactional abort."},
    {"TX_EXEC.MISC2", "Unfriendly TSX abort triggered by a vzeroupper instruction."},
    {"TX_EXEC.MISC3", "Unfriendly TSX abort triggered by a nest count that is too deep."},
    {"TX_EXEC.MISC4", "RTM region detected inside HLE."},
    {"TX_EXEC.MISC5", "Counts the number of times an HLE XACQUIRE instruction was executed inside an RTM transactional region."},
    {"TX_MEM.ABORT_CAPACITY", "Number of times a transactional abort was signaled due to a data capacity limitation for transactional reads or writes."},
    {"TX_MEM.ABORT_CONFLICT", "Number of times a TSX line had a cache conflict."},
    {"TX_MEM.ABORT_HLE_ELISION_BUFFER_MISMATCH", "Number of times a TSX Abort was triggered due to release/commit but data and address mismatch."},
    {"TX_MEM.ABORT_HLE_ELISION_BUFFER_NOT_EMPTY", "Number of times a TSX Abort was triggered due to commit but Lock Buffer not empty."},
    {"TX_MEM.ABORT_HLE_ELISION_BUFFER_UNSUPPORTED_ALIGNMENT", "Number of times a TSX Abort was triggered due to attempting an unsupported alignment from Lock Buffer."},
    {"TX_MEM.ABORT_HLE_STORE_TO_ELIDED_LOCK", "Number of times a TSX Abort was triggered due to a non-release/commit store to lock."},
    {"TX_MEM.HLE_ELISION_BUFFER_FULL", "Number of times we could not allocate Lock Buffer."},
    {"UOPS_DISPATCHED_PORT.PORT_0", "Counts, on the per-thread basis, cycles during which at least one uop is dispatched from the Reservation Station (RS) to port 0."},
    {"UOPS_DISPATCHED_PORT.PORT_1", "Counts, on the per-thread basis, cycles during which at least one uop is dispatched from the Reservation Station (RS) to port 1."},
    {"UOPS_DISPATCHED_PORT.PORT_2", "Counts, on the per-thread basis, cycles during which at least one uop is dispatched from the Reservation Station (RS) to port 2."},
    {"UOPS_DISPATCHED_PORT.PORT_3", "Counts, on the per-thread basis, cycles during which at least one uop is dispatched from the Reservation Station (RS) to port 3."},
    {"UOPS_DISPATCHED_PORT.PORT_4", "Counts, on the per-thread basis, cycles during which at least one uop is dispatched from the Reservation Station (RS) to port 4."},
    {"UOPS_DISPATCHED_PORT.PORT_5", "Counts, on the per-thread basis, cycles during which at least one uop is dispatched from the Reservation Station (RS) to port 5."},
    {"UOPS_DISPATCHED_PORT.PORT_6", "Counts, on the per-thread basis, cycles during which at least one uop is dispatched from the Reservation Station (RS) to port 6."},
    {"UOPS_DISPATCHED_PORT.PORT_7", "Counts, on the per-thread basis, cycles during which at least one uop is dispatched from the Reservation Station (RS) to port 7."},
    {"UOPS_EXECUTED.CORE", "Number of uops executed from any thread."},
    {"UOPS_EXECUTED.CORE_CYCLES_GE_1", "Cycles at least 1 micro-op is executed from any thread on physical core."},
    {"UOPS_EXECUTED.CORE_CYCLES_GE_2", "Cycles at least 2 micro-op is executed from any thread on physical core."},
    {"UOPS_EXECUTED.CORE_CYCLES_GE_3", "Cycles at least 3 micro-op is executed from any thread on physical core."},
    {"UOPS_EXECUTED.CORE_CYCLES_GE_4", "Cycles at least 4 micro-op is executed from any thread on physical core."},
    {"UOPS_EXECUTED.CORE_CYCLES_NONE", "Cycles with no micro-ops executed from any thread on physical core."},
    {"UOPS_EXECUTED.CYCLES_GE_1_UOP_EXEC", "Cycles where at least 1 uop was executed per-thread."},
    {"UOPS_EXECUTED.CYCLES_GE_2_UOPS_EXEC", "Cycles where at least 2 uops were executed per-thread."},
    {"UOPS_EXECUTED.CYCLES_GE_3_UOPS_EXEC", "Cycles where at least 3 uops were executed per-thread."},
    {"UOPS_EXECUTED.CYCLES_GE_4_UOPS_EXEC", "Cycles where at least 4 uops were executed per-thread."},
    {"UOPS_EXECUTED.STALL_CYCLES", "Counts cycles during which no uops were dispatched from the Reservation Station (RS) per thread."},
    {"UOPS_EXECUTED.THREAD", "Number of uops to be executed per-thread each cycle."},
    {"UOPS_EXECUTED.X87", "Counts the number of x87 uops executed."},
    {"UOPS_ISSUED.ANY", "Counts the number of uops that the Resource Allocation Table (RAT) issues to the Reservation Station (RS)."},
    {"UOPS_ISSUED.SLOW_LEA", "Number of slow LEA uops being allocated. A uop is generally considered SlowLea if it has 3 sources (e.g. 2 sources + immediate) regardless if as a result of LEA instruction or not."},
    {"UOPS_ISSUED.STALL_CYCLES", "Counts cycles during which the Resource Allocation Table (RAT) does not issue any Uops to the reservation station (RS) for the current thread."},
    {"UOPS_ISSUED.VECTOR_WIDTH_MISMATCH", "Counts the number of Blend Uops issued by the Resource Allocation Table (RAT) to the reservation station (RS) in order to preserve upper bits of vector registers. Starting with the Skylake microarchitecture, these Blend uops are needed since every Intel SSE instruction executed in Dirty Upper State needs to preserve bits 128-255 of the destination register. For more information, refer to “Mixing Intel AVX and Intel SSE Code” section of the Optimization Guide."},
    {"UOPS_RETIRED.RETIRE_SLOTS", "Counts the retirement slots used."},
    {"UOPS_RETIRED.STALL_CYCLES", "This event counts cycles without actually retired uops."},
    {"UOPS_RETIRED.TOTAL_CYCLES", "Number of cycles using always true condition (uops_ret < 16) applied to non PEBS uops retired event."},
    {"UNC_ARB_COH_TRK_REQUESTS.ALL", "Number of entries allocated. Account for Any type: e.g. Snoop, Core aperture, etc."},
    {"UNC_ARB_TRK_OCCUPANCY.ALL", "Each cycle count number of all Core outgoing valid entries. Such entry is defined as valid from its allocation till first of IDI0 or DRS0 messages is sent out. Accounts for Coherent and non-coherent traffic."},
    {"UNC_ARB_TRK_OCCUPANCY.CYCLES_WITH_ANY_REQUEST", "Cycles with at least one request outstanding is waiting for data return from memory controller. Account for coherent and non-coherent requests initiated by IA Cores, Processor Graphics Unit, or LLC."},
    {"UNC_ARB_TRK_REQUESTS.ALL", "Total number of Core outgoing entries allocated. Accounts for Coherent and non-coherent traffic."},
    {"UNC_ARB_TRK_REQUESTS.DRD_DIRECT", "Number of Core coherent Data Read entries allocated in DirectData mode."},
    {"UNC_ARB_TRK_REQUESTS.WRITES", "Number of Writes allocated - any write transactions: full/partials writes and evictions."},
    {"UNC_CBO_CACHE_LOOKUP.ANY_ES", "L3 Lookup any request that access cache and found line in E or S-state."},
    {"UNC_CBO_CACHE_LOOKUP.ANY_I", "L3 Lookup any request that access cache and found line in I-state."},
    {"UNC_CBO_CACHE_LOOKUP.ANY_M", "L3 Lookup any request that access cache and found line in M-state."},
    {"UNC_CBO_CACHE_LOOKUP.ANY_MESI", "L3 Lookup any request that access cache and found line in MESI-state."},
    {"UNC_CBO_CACHE_LOOKUP.READ_ES", "L3 Lookup read request that access cache and found line in E or S-state."},
    {"UNC_CBO_CACHE_LOOKUP.READ_I", "L3 Lookup read request that access cache and found line in I-state."},
    {"UNC_CBO_CACHE_LOOKUP.READ_MESI", "L3 Lookup read request that access cache and found line in any MESI-state."},
    {"UNC_CBO_CACHE_LOOKUP.WRITE_ES", "L3 Lookup write request that access cache and found line in E or S-state."},
    {"UNC_CBO_CACHE_LOOKUP.WRITE_M", "L3 Lookup write request that access cache and found line in M-state."},
    {"UNC_CBO_CACHE_LOOKUP.WRITE_MESI", "L3 Lookup write request that access cache and found line in MESI-state."},
    {"UNC_CBO_XSNP_RESPONSE.HIT_XCORE", "A cross-core snoop initiated by this Cbox due to processor core memory request which hits a non-modified line in some processor core."},
    {"UNC_CBO_XSNP_RESPONSE.HITM_XCORE", "A cross-core snoop initiated by this Cbox due to processor core memory request which hits a modified line in some processor core."},
    {"UNC_CBO_XSNP_RESPONSE.MISS_EVICTION", "A cross-core snoop resulted from L3 Eviction which misses in some processor core."},
    {"UNC_CBO_XSNP_RESPONSE.MISS_XCORE", "A cross-core snoop initiated by this Cbox due to processor core memory request which misses in some processor core."},
    {"UNC_CLOCK.SOCKET", "This 48-bit fixed counter counts the UCLK cycles."},
};
*/
