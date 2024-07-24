#include "../common/Global.h"
#include "../common/TestBase.h"
NS_TEST_BEGIN

// Provided by VK_KHR_maintenance5
typedef VkFlags64 VkBufferUsageFlags2KHR;


// Provided by VK_KHR_maintenance5
typedef struct VkBufferUsageFlags2CreateInfoKHR {
    VkStructureType           sType;
    const void* pNext;
    VkBufferUsageFlags2KHR    usage;
} VkBufferUsageFlags2CreateInfoKHR;







NS_TEST_END