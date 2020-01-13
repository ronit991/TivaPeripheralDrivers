#include<stdint.h>
#define __vol volatile

typedef struct
{
	__vol uint32_t  DID0;                              /*!< Device Identification 0                                               */
  __vol uint32_t  DID1;                              /*!< Device Identification 1                                               */
  __vol uint32_t  DC0;                               /*!< Device Capabilities 0                                                 */
				uint32_t  RESERVED;
  __vol uint32_t  DC1;                               /*!< Device Capabilities 1                                                 */
  __vol uint32_t  DC2;                               /*!< Device Capabilities 2                                                 */
  __vol uint32_t  DC3;                               /*!< Device Capabilities 3                                                 */
  __vol uint32_t  DC4;                               /*!< Device Capabilities 4                                                 */
  __vol uint32_t  DC5;                               /*!< Device Capabilities 5                                                 */
  __vol uint32_t  DC6;                               /*!< Device Capabilities 6                                                 */
  __vol uint32_t  DC7;                               /*!< Device Capabilities 7                                                 */
  __vol uint32_t  DC8;
}sysctl;