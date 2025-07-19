#include <stdint.h>
#include <common/runtime_svc.h>
#include <lib/smccc.h>
#include <smccc_helpers.h>


#define PLUSONE_OEN  GET_SMC_OEN(RK_SVC_OEM_PLUSONE_FID)  /* = 0xC2 */
#define PLUSONE_TYPE GET_SMC_TYPE(RK_SVC_OEM_PLUSONE_FID)/* = SMC_TYPE_FAST */

#define RK_SVC_OEM_PLUSONE_FID  0xC200FF01


static uintptr_t plusone_smc_handler(uint32_t      smc_fid,
                                     u_register_t  x1, u_register_t x2,
                                     u_register_t  x3, u_register_t x4,
                                     void         *cookie,
                                     void         *handle,
                                     u_register_t  flags)
{       

        if (smc_fid != RK_SVC_OEM_PLUSONE_FID)
                SMC_RET1(handle, SMC_UNK);

        SMC_RET1(handle, x1 + 10);
}


DECLARE_RT_SVC(
  rk_plusone,
  PLUSONE_OEN,
  PLUSONE_OEN,
  SMC_TYPE_FAST,
  NULL,
  plusone_smc_handler
);