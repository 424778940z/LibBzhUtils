#ifndef RUNANDCHECK_HPP
#define RUNANDCHECK_HPP

#include <iostream>
#include <string>

// REMEMBER, RAC_ret will always hold return of your function call
// RAC_ret is "auto" type, as long as your function call returns something
// and you checking block are compairing it with right type, then all good
// Don't as me if my function call is void, well if no return val, then what to check?

// usage example for RAC_ADVANCE

// --- define your custom WAHT_TO_DO_WHEN_FALSE block
// #define RAC_ON_FALSE_USBGX                                                                         \
//   {                                                                                                \
//     RAC_ON_FALSE                                                                                   \
//     std::cout << "USBGX_ERR  -> " << usbg_strerror(static_cast<usbg_error>(RAC_ret)) << std::endl; \
//     if ( s != nullptr )                                                                            \
//     {                                                                                              \
//       usbg_cleanup(s);                                                                             \
//     }                                                                                              \
//     return false;                                                                                  \
//   }

// --- then later call like this anywhere in your file
// RAC_ADVANCE(
//     usbg_create_gadget(s, USB_GADGET_NAME, &g_attrs, &g_strs, &g), (RAC_ret == USBG_SUCCESS),
//     RAC_ON_FALSE_USBGX
// );

// --- or you could even use like a lambda for WAHT_TO_DO_WHEN_FALSE block
// RAC_ADVANCE(
//     usbg_create_gadget(s, USB_GADGET_NAME, &g_attrs, &g_strs, &g), (RAC_ret == USBG_SUCCESS),
//     {
//       RAC_ON_FALSE_USBGX
//       MORE_THINGS_TODO
//       exit(-1);
//     }
// );

// --- in case you also need the return value
// auto return_val_that_i_need;
// RAC_ADVANCE(
//     return_val_that_i_need = usbg_create_gadget(s, USB_GADGET_NAME, &g_attrs, &g_strs, &g),
//     (RAC_ret == USBG_SUCCESS), RAC_ON_FALSE_USBGX
// );

// there is no use for namespace here since this library all macro based (for now)
// namespace bzh_utils
// {
//     namespace checks
//     {

#define RAC_ON_FALSE                                                  \
  {                                                                   \
    std::cout << "*****************" << std::endl                     \
              << "RAC FAILED" << std::endl                            \
              << "CALL -> " << func_call_str << std::endl             \
              << "CONDITION -> " << expect_condition_str << std::endl \
              << "RET  -> " << std::to_string(RAC_ret) << std::endl;  \
  }

// RAC_ADVANCE(function(what,ever), RAC_CHECK_LOGIC, WAHT_TO_DO_WHEN_FALSE)
#define RAC_ADVANCE(func_call, expect_condition, on_false) \
  {                                                        \
    auto RAC_ret = (func_call);                            \
    std::string func_call_str(#func_call);                 \
    std::string expect_condition_str(#expect_condition);   \
    if ( !(expect_condition) )                             \
    {                                                      \
      on_false                                             \
    }                                                      \
  }

// RAC_SIMPLE(function(what,ever), RAC_CHECK_LOGIC)
#define RAC_SIMPLE(func_call, expect_condition) RAC_ADVANCE(func_call, expect_condition, RAC_ON_FALSE)


//     }; // namespace checks

// }; // namespace bzh_utils

#endif // RUNANDCHECK_HPP
