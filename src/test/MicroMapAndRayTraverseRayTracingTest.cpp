#include "MicroMapAndRayTraverseRayTracingTest.h"
NS_TEST_BEGIN

MicromapAndRayTraverseRayTracingTest::MicromapAndRayTraverseRayTracingTest()
{
}

void MicromapAndRayTraverseRayTracingTest::run()
{
}

MicromapAndRayTraverseRayTracingTest::~MicromapAndRayTraverseRayTracingTest()
{
}

void MicromapAndRayTraverseRayTracingTest::MicromapTest()
{
	/*
	���ٽṹ��֯ray tracing��Ҫ��geometry��Ȼ����һЩ����£��洢����֯һЩ��geometry��أ������������ε�geometry������Ϣ�����洦�ģ�micromap������֯��һЩ��Ӧ��ϸ�ֵ�΢�����ε���Ϣ�����Դ��� bottom level acceleration structure��ӵ�������geometry��ʱ��

	opacity micromap�洢���� intersection opacity ���μ�p3333������Ϣ

	displacement micromap�洢�滻sub-triangle �������Ϣ ���μ�Displacement Micromap. p3324��

	����ʹ��micromap�Ĺ����Լ���������������һ��micromap
	*/

	VkMicromapEXT micromapEXT{};
	VkCommandBuffer commandBuffer{/*��������һ����Ч��VkCommandBuffer*/ };


	// Micromaps �μ�p3294
	{
		//����micromap
		VkMicromapBuildInfoEXT micromapBuildInfoEXT{};//�ýṹ���һЩ�����Ϣ��p3299
		micromapBuildInfoEXT.sType = VK_STRUCTURE_TYPE_MICROMAP_BUILD_INFO_EXT;
		micromapBuildInfoEXT.pNext = nullptr;
		micromapBuildInfoEXT.type = VK_MICROMAP_TYPE_OPACITY_MICROMAP_EXT;// VkMicromapTypeEXTֵָ��Ҫ������micromap����
		micromapBuildInfoEXT.flags = VK_BUILD_MICROMAP_PREFER_FAST_TRACE_BIT_EXT;//VkBuildMicromapFlagBitsEXT���ֵλ����ָ������Ĳ���
		micromapBuildInfoEXT.mode = VK_BUILD_MICROMAP_MODE_BUILD_EXT;// VkBuildMicromapModeEXTֵָ��Ҫִ�еĲ���,VK_BUILD_MICROMAP_MODE_BUILD_EXT ָ��ʹ��ָ�������ݹ���micromap
		micromapBuildInfoEXT.dstMicromap = micromapEXT;//ָ��Ҫ������micromap�ľ��
		micromapBuildInfoEXT.usageCountsCount = 1;//ָ����������micromap��С��VkMicromapUsageEXT������
		VkMicromapUsageEXT micromapUsageEXT{};
		{
			micromapUsageEXT.count = 1;//Ϊmicromap��subdivisionLevel �Լ� format �����ʹ�ø�ʽ�������ε�����
			micromapUsageEXT.format = 0;//Ϊʹ�ø�ʽ��format
			/*
			VkOpacityMicromapFormatEXT��
			VK_OPACITY_MICROMAP_FORMAT_2_STATE_EXT:  ָ������micromap format��ÿ��subtriangle��Ӧ��һ��bitָ������ȫ��͸��������ȫ͸��
			VK_OPACITY_MICROMAP_FORMAT_4_STATE_EXT:  ָ������micromap format��ÿ��subtriangle��Ӧ������bit��������ͼ�p3333 ray traversal


			VkDisplacementMicromapFormatNV:
			VK_DISPLACEMENT_MICROMAP_FORMAT_64_TRIANGLES_64_BYTES_NV: ָ������micromap format��64��ֵ���滻��64��micro-triangles����Ϊ64���ֽڣ��μ�Displacement Micromap Encoding p3324
			VK_DISPLACEMENT_MICROMAP_FORMAT_256_TRIANGLES_128_BYTES_NV:  ָ������micromap format��128��ֵ���滻��128��micro-triangles����Ϊ64���ֽڣ��μ�Displacement Micromap Encoding p3324
			VK_DISPLACEMENT_MICROMAP_FORMAT_1024_TRIANGLES_128_BYTES_NV:  ָ������micromap format��1024��ֵ���滻��128��micro-triangles����Ϊ64���ֽڣ��μ�Displacement Micromap Encoding p3324
			*/
			micromapUsageEXT.subdivisionLevel = 0;//Ϊʹ�ø�ʽ�� subdivision level
			/*
			VkMicromapUsageEXT��Ч�÷�:
			1.���micromap��VkMicromapTypeEXT ΪVK_MICROMAP_TYPE_OPACITY_MICROMAP_EXT����1��format����ΪVK_OPACITY_MICROMAP_FORMAT_2_STATE_EXT���� VK_OPACITY_MICROMAP_FORMAT_4_STATE_EXT
																						 ��2�����formatΪVK_OPACITY_MICROMAP_FORMAT_2_STATE_EXT����subdivisionLevel ����С�ڵ���VkPhysicalDeviceOpacityMicromapPropertiesEXT::maxOpacity2StateSubdivisionLevel
																						 ��3�����formatΪVK_OPACITY_MICROMAP_FORMAT_4_STATE_EXT����subdivisionLevel ����С�ڵ���VkPhysicalDeviceOpacityMicromapPropertiesEXT::maxOpacity4StateSubdivisionLevel
			2.���micromap��VkMicromapTypeEXT ΪVK_MICROMAP_TYPE_DISPLACEMENT_MICROMAP_NV����1��format����ΪVK_DISPLACEMENT_MICROMAP_FORMAT_64_TRIANGLES_64_BYTES_NV, VK_DISPLACEMENT_MICROMAP_FORMAT_256_TRIANGLES_128_BYTES_NV ���� VK_DISPLACEMENT_MICROMAP_FORMAT_1024_TRIANGLES_128_BYTES_NV
																							 ��2��subdivisionLevel ����С�ڵ���VkPhysicalDeviceDisplacementMicromapPropertiesNV::maxDisplacementMicromapSubdivisionLevel

			*/
		}
		micromapBuildInfoEXT.pUsageCounts = &micromapUsageEXT;//һ��VkMicromapUsageEXT ������ָ��
		micromapBuildInfoEXT.ppUsageCounts = VK_NULL_HANDLE;//һ��VkMicromapUsageEXT ������ָ�������ָ�룬��pUsageCountsֻ����һ����ΪVK_NULL_HANDLE
		micromapBuildInfoEXT.data = VkDeviceOrHostAddressConstKHR{ .deviceAddress/*ͨ��vkGetBufferDeviceAddressKHR����*/ = 0/*.hostAddress host�˵�ַ*/ /*��������һ����Ч��VkDeviceOrHostAddressConstKHR*/ };//����micromap���ݵ� device ���� host�˵�const�ڴ��ַ
		micromapBuildInfoEXT.scratchData = VkDeviceOrHostAddressKHR{ .deviceAddress/*ͨ��vkGetBufferDeviceAddressKHR����*/ = 0/*.hostAddress host�˵�ַ*/ /*��������һ����Ч��VkDeviceOrHostAddressKHR*/ };//Ϊ���ڹ����� scratch memory �� device ���� host�˵��ڴ��ַ
		//triangleArray�е�����
		{
			VkMicromapTriangleEXT micromapTriangleEXT{};
			micromapTriangleEXT.dataOffset = 0;//Ϊ�����������ݵ���ʼ�ֽ�ƫ����
			micromapTriangleEXT.format = 0;//Ϊ�������ε�subdivision level
			micromapTriangleEXT.subdivisionLevel = 0;//Ϊ�������ε�format

			/*
			VkMicromapTriangleEXT��Ч�÷�:
			1.���micromap��VkMicromapTypeEXT ΪVK_MICROMAP_TYPE_OPACITY_MICROMAP_EXT����1��format����ΪVK_OPACITY_MICROMAP_FORMAT_2_STATE_EXT���� VK_OPACITY_MICROMAP_FORMAT_4_STATE_EXT
																						 ��2�����formatΪVK_OPACITY_MICROMAP_FORMAT_2_STATE_EXT����subdivisionLevel ����С�ڵ���VkPhysicalDeviceOpacityMicromapPropertiesEXT::maxOpacity2StateSubdivisionLevel
																						 ��3�����formatΪVK_OPACITY_MICROMAP_FORMAT_4_STATE_EXT����subdivisionLevel ����С�ڵ���VkPhysicalDeviceOpacityMicromapPropertiesEXT::maxOpacity4StateSubdivisionLevel
			2.���micromap��VkMicromapTypeEXT ΪVK_MICROMAP_TYPE_DISPLACEMENT_MICROMAP_NV����1��format����ΪVK_DISPLACEMENT_MICROMAP_FORMAT_64_TRIANGLES_64_BYTES_NV, VK_DISPLACEMENT_MICROMAP_FORMAT_256_TRIANGLES_128_BYTES_NV ���� VK_DISPLACEMENT_MICROMAP_FORMAT_1024_TRIANGLES_128_BYTES_NV
																							 ��2��subdivisionLevel ����С�ڵ���VkPhysicalDeviceDisplacementMicromapPropertiesNV::maxDisplacementMicromapSubdivisionLevel

			*/

		}
		micromapBuildInfoEXT.triangleArray = VkDeviceOrHostAddressConstKHR{ .deviceAddress/*ͨ��vkGetBufferDeviceAddressKHR����*/ = 0/*.hostAddress host�˵�ַ*/ /*��������һ����Ч��VkDeviceOrHostAddressConstKHR*/ };//Ϊ����VkMicromapTriangleEXT ���ݵ� device ���� host�˵�const�ڴ��ַ
		micromapBuildInfoEXT.triangleArrayStride = 12;//ָ��triangleArray ������Ԫ��֮����ֽڲ���
		/*
		VkMicromapBuildInfoEXT��Ч�÷�:
		1.pUsageCounts��ppUsageCounts��ֻ��һ��Ϊ��Ч��ָ�룬����һ������ΪVK_NULL_HANDLE
		2.���typeΪVK_MICROMAP_TYPE_OPACITY_MICROMAP_EXT����VkMicromapUsageEXT::format��VkMicromapTriangleEXT::format ��������Ч��VkOpacityMicromapFormatEXTֵ
		3.���typeΪVK_MICROMAP_TYPE_DISPLACEMENT_MICROMAP_NV����VkMicromapUsageEXT::format��VkMicromapTriangleEXT::format ��������Ч��VkDisplacementMicromapFormatNVֵ

		*/




		/*
		���ж� VkMicromapBuildInfoEXT::scratchData,VkMicromapBuildInfoEXT::dstMicromap, VkMicromapBuildInfoEXT::data�Լ�VkMicromapBuildInfoEXT::triangleArray��VK_PIPELINE_STAGE_2_MICROMAP_BUILD_BIT_EXT pipeline stageͬ����
		VkMicromapBuildInfoEXT::scratchData ��(VK_ACCESS_2_MICROMAP_READ_BIT_EXT | VK_ACCESS_2_MICROMAP_WRITE_BIT_EXT)���з���
		VkMicromapBuildInfoEXT::dstMicromap ��VK_ACCESS_2_MICROMAP_WRITE_BIT_EXT ���з���
		VkMicromapBuildInfoEXT::data�Լ�VkMicromapBuildInfoEXT::triangleArray ��VK_ACCESS_2_MICROMAP_READ_BIT_EXT ���з���
		*/
		vkCmdBuildMicromapsEXT(commandBuffer, 1, &micromapBuildInfoEXT);
		/*
		vkCmdBuildMicromapsEXT��Ч�÷�:
		1.���κ�pInfos[i]��dstMicromap ������VkMicromapCreateInfoEXT::size���ڵ��ڵ���vkGetMicromapBuildSizesEXT����pBuildInfo = pInfos[i]��ѯ���ص��ڴ��С���д���
		2.pInfos��ÿ��Ԫ�ص�mode������һ����Ч��VkBuildMicromapModeEXT
		3.pInfos��ÿ��Ԫ�ص�dstMicromap������һ����Ч��VkMicromapEXT ���
		4.pInfos��ÿ��Ԫ�ص�type ����ƥ�䴴��dstMicromap ʱ��VkMicromapCreateInfoEXT::type
		5.��������ʵ�pInfos���κ�Ԫ�ص�dstMicromap�ĵײ��ڴ�ķ�Χ֮�䲻�����ص�
		6.��������ʵ�pInfos���κ�Ԫ�ص�dstMicromap���ܺ��κ�Ԫ��(������ͬԪ��)��scratchData�ĵײ��ڴ�ķ�Χ֮�����ص�
		7.��������ʵ�pInfos���κ�Ԫ�ص�scratchData�ĵײ��ڴ�ķ�Χ֮�䲻�����ص�
		8.��pInfos��ÿ��Ԫ�أ����ڴ�����dstMicromap��buffer�����Ѿ��󶨵�device memory
		9.���pInfos[i].mode ΪVK_BUILD_MICROMAP_MODE_BUILD_EXT������ pInfos[i].scratchData.deviceAddress �Լ� pInfos[i].scratchData.deviceAddress + N - 1 ֮������е�ַ��������ͬbuffer�ĵ�ַ��Χ�ڣ�����NΪ����vkGetMicromapBuildSizesEXT��������ͬVkMicromapBuildInfoEXT��primitive count���ص�VkMicromapBuildSizesInfoEXT::buildScratchSize
		10. pInfos[i]��data�Լ�triangleArray �漰����buffer������VK_BUFFER_USAGE_MICROMAP_BUILD_INPUT_READ_ONLY_BIT_EXT����
		11.pInfos[i]��ÿ��pInfos[i].scratchData.deviceAddress �漰����buffer������VK_BUFFER_USAGE_STORAGE_BUFFER_BIT ����
		12.��pInfos��ÿ��Ԫ�أ���scratchData.deviceAddress, data.deviceAddress�Լ�triangleArray.deviceAddress ��������Ч��ͨ��vkGetBufferDeviceAddress ��ȡ�ĵ�ַ
		13.��pInfos��ÿ��Ԫ�أ����scratchData.deviceAddress, data.deviceAddress�Լ�triangleArray.deviceAddress �漰��non-sparse��buffer�����buffer�����Ѿ��󶨵������������ĵ�����VkDeviceMemory����
		14.��pInfos��ÿ��Ԫ�أ���scratchData.deviceAddress ������VkPhysicalDeviceAccelerationStructurePropertiesKHR::minAccelerationStructureScratchOffsetAlignment��������
		15.��pInfos��ÿ��Ԫ�أ���triangleArray.deviceAddress �Լ� data.deviceAddress������256 ��������

		*/


		//------------------------------------

		/*
		����һ�������Ҫ����micromap�����ݾͿ��Զ�����п��������ڿ���ǰ��Ҫ��ѯdst micromap���ڴ��С����
		*/

		//��ѯmicromap��С���� ����pMicromaps��Ԫ����VK_PIPELINE_STAGE_2_MICROMAP_BUILD_BIT_EXT pipeline stageͬ������VK_ACCESS_2_MICROMAP_READ_BIT_EXT����
		vkCmdWriteMicromapsPropertiesEXT(commandBuffer, 1, &micromapEXT,
			VK_QUERY_TYPE_ACCELERATION_STRUCTURE_COMPACTED_SIZE_KHR/*queryType,ָ����ѯ����*/, VkQueryPool{/*��������һ����Ч��VkQueryPool*/ }/*queryPool��ָ�������ѯ�����VkQueryPool*/, 0/*firstQuery,ָ����Ų�ѯ����ĵ�һ��query������*/);
		/*
		vkCmdWriteMicromapsPropertiesEXT��Ч�÷�:
		1.queryPool ������ƥ��queryType����
		2.��queryPool �Լ�firstQuery ָ����queries ������unavailable ��
		3.���ڴ���pMicrmaps��ÿ��micromap��buffer�����Ѿ��󶨵�device memory
		4.firstQuery + micromapCount ����С�ڵ���queryPool��queries������
		5.pMicromaps�е�����micromaps �����ڸ���ִ��ǰ������
		6.���queryTypeΪVK_QUERY_TYPE_MICROMAP_COMPACTED_SIZE_EXT�� pMicromaps�е�����micromaps ������VK_BUILD_MICROMAP_ALLOW_COMPACTION_BIT_EXT ����
		7.queryType ����ΪVK_QUERY_TYPE_MICROMAP_COMPACTED_SIZE_EXT ����VK_QUERY_TYPE_MICROMAP_SERIALIZATION_SIZE_EXT
		*/




		VkCopyMicromapInfoEXT copyMicromapInfoEXT{};
		copyMicromapInfoEXT.sType = VK_STRUCTURE_TYPE_COPY_MICROMAP_INFO_EXT;
		copyMicromapInfoEXT.pNext = nullptr;
		copyMicromapInfoEXT.mode = VK_COPY_MICROMAP_MODE_CLONE_EXT;/* VkCopyMicromapModeEXTֵָ�������ڼ�ִ�еĶ������
		VkCopyMicromapModeEXT:
		VK_COPY_MICROMAP_MODE_CLONE_EXT:  ����һ����src��dst��micromap��ֱ�ӿ�����dst micromap�����src����ͬ�Ĳ�������
		VK_COPY_MICROMAP_MODE_SERIALIZE_EXT: ��semi-opaque format���л�micromap�����л���ͷ����ʽ��Ϣ��p3308�������Ա����ݵ�ʵ�����¼���
		VK_COPY_MICROMAP_MODE_DESERIALIZE_EXT:  ��semi-opaque format�����л���һ��micromap
		VK_COPY_MICROMAP_MODE_COMPACT_EXT:  ����һ����src��dst��ѹ���汾��Ϣ��dst �����Դ�С����Ϊ����src��������vkCmdWriteMicromapsPropertiesEXT���ص�ֵ����
		*/
		copyMicromapInfoEXT.src = VkMicromapEXT{/*��������һ����Ч��VkMicromapEXT*/ };//ָ��������source micromap
		copyMicromapInfoEXT.dst = micromapEXT;//ָ��������destination micromap
		/*
		VkCopyMicromapInfoEXT��Ч�÷�:
		1.mode ����ΪVK_COPY_MICROMAP_MODE_COMPACT_EXT ���� VK_COPY_MICROMAP_MODE_CLONE_EXT
		2.src micromap�����ڸ�����ִ��ǰ������
		3.���mode ΪVK_COPY_MICROMAP_MODE_COMPACT_EXT����src������VK_BUILD_MICROMAP_ALLOW_COMPACTION_BIT_EXT����
		4.���ڴ���src�Լ�dst��buffer����󶨵�device memory��
		*/


		//����micromap ,   ��pInfo->src �Լ� pInfo->dst��VK_PIPELINE_STAGE_2_MICROMAP_BUILD_BIT_EXT pipeline stageͬ������VK_ACCESS_2_MICROMAP_READ_BIT_EXT ���� VK_ACCESS_2_MICROMAP_WRITE_BIT_EXT����
		vkCmdCopyMicromapEXT(commandBuffer, &copyMicromapInfoEXT); //���ڴ���pInfo->src �Լ� pInfo->dst��buffer�����Ѿ��󶨵�device memory��




		VkCopyMicromapToMemoryInfoEXT copyMicromapToMemoryInfoEXT{};
		copyMicromapToMemoryInfoEXT.sType = VK_STRUCTURE_TYPE_COPY_MICROMAP_TO_MEMORY_INFO_EXT;
		copyMicromapToMemoryInfoEXT.pNext = nullptr;
		copyMicromapToMemoryInfoEXT.mode = VK_COPY_MICROMAP_MODE_SERIALIZE_EXT;//VkCopyMicromapModeEXTֵָ�������ڼ�ִ�еĶ������
		copyMicromapToMemoryInfoEXT.src = micromapEXT;//ָ��������source micromap
		copyMicromapToMemoryInfoEXT.dst = VkDeviceOrHostAddressKHR{ .deviceAddress/*ͨ��vkGetBufferDeviceAddressKHR����*/ = 0/*.hostAddress host�˵�ַ*/ /*��������һ����Ч��VkDeviceOrHostAddressKHR*/ };//Ϊ����micromap��dstination memory�� device ���� host�˵��ڴ��ַ
		/*
		VkCopyMicromapToMemoryInfoEXT��Ч�÷�:
		1.src micromap�����ڸ�����ִ��ǰ����
		2.dst�󶨵�memory�Ĵ�С������src���л��Ĵ�С���� vkWriteMicromapsPropertiesEXT ���� vkCmdWriteMicromapsPropertiesEXT ����query typeΪ VK_QUERY_TYPE_MICROMAP_SERIALIZATION_SIZE_EXT���ص�ֵ
		3.mode ����ΪVK_COPY_MICROMAP_MODE_SERIALIZE_EXT
		*/

		/*
		����һ��micromap���л���device memory ���� vkCopyMicromapToMemoryEXT������ͬ�����ֻ����������Ὣ���д��device memory�У���������Ա�vkCmdCopyMemoryToMicromapEXT ���� vkCopyMemoryToMicromapEXTʹ��
		��pInfo->src ����pInfo->dst �� VK_PIPELINE_STAGE_2_MICROMAP_BUILD_BIT_EXT pipeline stage ͬ��

		��pInfo->src��VK_ACCESS_2_MICROMAP_READ_BIT_EXT���ʣ���pInfo->dst.deviceAddress�� VK_ACCESS_TRANSFER_WRITE_BIT����
		*/
		vkCmdCopyMicromapToMemoryEXT(commandBuffer, &copyMicromapToMemoryInfoEXT);
		/*
		vkCmdCopyMicromapToMemoryEXT��Ч�÷�:
		1.pInfo->dst.deviceAddress ������һ���󶨵�device memory����Ч��device address���������뵽256�ֽ�
		2.���pInfo->dst.deviceAddress ��ָ��buffer��non-sparse�����buffer����󶨵������������ĵ�����VkDeviceMemory����
		3.���ڴ���pInfo->src ��buffer����󶨵�device memory
		*/




		VkCopyMemoryToMicromapInfoEXT copyMemoryToMicromapInfoEXT{};
		copyMemoryToMicromapInfoEXT.sType = VK_STRUCTURE_TYPE_COPY_MEMORY_TO_MICROMAP_INFO_EXT;
		copyMemoryToMicromapInfoEXT.pNext = nullptr;
		copyMemoryToMicromapInfoEXT.mode = VK_COPY_MICROMAP_MODE_DESERIALIZE_EXT;//VkCopyMicromapModeEXTֵָ�������ڼ�ִ�еĶ������
		copyMemoryToMicromapInfoEXT.src = VkDeviceOrHostAddressConstKHR{ .deviceAddress/*ͨ��vkGetBufferDeviceAddressKHR����*/ = 0/*.hostAddress host�˵�ַ*/ /*��������һ����Ч��VkDeviceOrHostAddressConstKHR*/ };//Ϊ����micromap��source memory�� device ���� host�˵�const�ڴ��ַ
		copyMemoryToMicromapInfoEXT.dst = micromapEXT;//ָ��������destination micromap
		/*
		VkCopyMemoryToMicromapInfoEXT��Ч�÷�:
		1.src��ָ��source memory�б������֮ǰͨ��vkCmdCopyMicromapToMemoryEXT���л�������
		2.mode ����ΪVK_COPY_MICROMAP_MODE_DESERIALIZE_EXT
		3.src�е����ݵı�����һ����destination physical device���ݵ�format ����vkGetDeviceMicromapCompatibilityEXT���ص���Ϣ
		4.dst ���ݴ�С�����Դ��ڵ���src�е����л����ݴ�С����

		*/


		/*
		����device memory�����л���һ��micromap����vkCopyAccelerationStructureToMemoryKHR������ͬ���
		��pInfo->src ����pInfo->dst ��  VK_PIPELINE_STAGE_2_MICROMAP_BUILD_BIT_EXT pipeline stageͬ��

		��pInfo->src.deviceAddress��VK_ACCESS_TRANSFER_READ_BIT���ʣ���pInfo->dst�� VK_ACCESS_2_MICROMAP_READ_BIT_EXT����

		��������Խ�������vkCmdCopyMicromapToMemoryEXT ���� vkCopyMicromapToMemoryEXT.������micromap
		*/
		vkCmdCopyMemoryToMicromapEXT(commandBuffer, &copyMemoryToMicromapInfoEXT);
		/*
		vkCmdCopyMemoryToMicromapEXT��Ч�÷�:
		1.pInfo->src.deviceAddress ������һ����Ч�İ󶨵�device memory��device address���ұ�����뵽256�ֽ�
		2.���pInfo->src.deviceAddress ��ָ��buffer��non-sparse�����buffer����󶨵������������ĵ�����VkDeviceMemory����
		3.���ڴ���pInfo->dst ��buffer����󶨵�device memory
		*/


		VkMicromapVersionInfoEXT micromapVersionInfoEXT{};
		micromapVersionInfoEXT.sType = VK_STRUCTURE_TYPE_MICROMAP_VERSION_INFO_EXT;
		micromapVersionInfoEXT.pNext = nullptr;
		uint8_t version = 0;
		micromapVersionInfoEXT.pVersionData = &version;//������vkCmdCopyMicromapToMemoryEXT���� vkCopyMicromapToMemoryEXT ִ���Ƕ���İ汾ͷ��Ϣ������ָ�룬ָ��2��VK_UUID_SIZE ��uint8_tֵ

		VkAccelerationStructureCompatibilityKHR cccelerationStructureCompatibilityKHR{};
		//���һЩ���л���micromap�Ƿ����device
		vkGetDeviceMicromapCompatibilityEXT(device, &micromapVersionInfoEXT, &cccelerationStructureCompatibilityKHR);// micromap ���Ա��뿪��
	}


	//Host Micromap Operations  �μ�p3314
	{
		/*
		��� micromapHostCommands���Կ�������ʵ��Ҳ�ṩ����host�˶�micromap�Ĳ���:
		
		host��							   ��Ӧ             device��
		vkBuildMicromapsEXT				    ->				vkCmdBuildMicromapsEXT
		vkCopyMicromapEXT					->				vkCmdCopyMicromapEXT
		vkCopyMicromapToMemoryEXT			->				vkCmdCopyMicromapToMemoryEXT
		vkCopyMemoryToMicromapEXT			->				vkCmdCopyMemoryToMicromapEXT
		vkWriteMicromapsPropertiesEXT		->				vkCmdWriteMicromapsPropertiesEXT
		

		host�˲���micromap��������ʵ�micromap����󶨵�host-visible���ڴ棬������micromap�����������������ݱ�������host�˵ĵ�ַ������device��
		*/

		VkMicromapBuildInfoEXT micromapBuildInfoEXT{/*��������һ����Ч��VkMicromapBuildInfoEXT*/};//ǰ���Ѿ��������ˣ����ﲻ�ٸ���

		//��host�˹���micromap  ,��Ч��vkCmdBuildMicromapsEXT����������ǰ������������ﲻ�ٸ����������������κ��ڴ���ʿ���
		vkBuildMicromapsEXT(device, VkDeferredOperationKHR{/*��������һ����Ч��VkDeferredOperationKHR*/ }, 1, & micromapBuildInfoEXT);
		/*
		vkBuildMicromapsEXT��Ч�÷�:
		1.���κ�pInfos[i]��dstMicromap ������VkMicromapCreateInfoEXT::size���ڵ��ڵ���vkGetMicromapBuildSizesEXT����pBuildInfo = pInfos[i]��ѯ���ص��ڴ��С���д���
		2.pInfos��ÿ��Ԫ�ص�mode������һ����Ч��VkBuildMicromapModeEXT
		3.pInfos��ÿ��Ԫ�ص�dstMicromap������һ����Ч��VkMicromapEXT ���
		4.pInfos��ÿ��Ԫ�ص�type ����ƥ�䴴��dstMicromap ʱ��VkMicromapCreateInfoEXT::type
		5.��������ʵ�pInfos���κ�Ԫ�ص�dstMicromap�ĵײ��ڴ�ķ�Χ֮�䲻�����ص�
		6.��������ʵ�pInfos���κ�Ԫ�ص�dstMicromap���ܺ��κ�Ԫ��(������ͬԪ��)��scratchData�ĵײ��ڴ�ķ�Χ֮�����ص�
		7.��������ʵ�pInfos���κ�Ԫ�ص�scratchData�ĵײ��ڴ�ķ�Χ֮�䲻�����ص�
		8.��pInfos��ÿ��Ԫ�أ����ڴ�����dstMicromap��buffer�����Ѿ��󶨵�host-visible device memory
		9.pInfos�е�ÿ��Ԫ�أ�����Ԫ�ص�data.hostAddress���õı�������Ч��host memory
		10.pInfos�е�ÿ��Ԫ�أ�����Ԫ�ص�triangleArray.hostAddress���õı�������Ч��host memory
		11.VkPhysicalDeviceOpacityMicromapFeaturesEXT::micromapHostCommands ���Ա��뿪��
		12.���pInfos[i].mode ΪVK_BUILD_MICROMAP_MODE_BUILD_EXT������ pInfos[i].scratchData.hostAddress �Լ� pInfos[i].scratchData.hostAddress + N - 1 ֮������е�ַ������Ч��host memory������NΪ����vkGetMicromapBuildSizesEXT��������ͬVkMicromapBuildInfoEXT��primitive count���ص�VkMicromapBuildSizesInfoEXT::buildScratchSize
		13.pInfos�е�ÿ��Ԫ�أ����ڴ�����dstMicromap��buffer����󶨵�memory������memory������multiple instances �Ϸ���
		*/



		VkCopyMicromapInfoEXT copyMicromapInfoEXT{/*��������һ����Ч��VkCopyMicromapInfoEXT*/ };//ǰ���Ѿ����������ﲻ�ٸ���
		//��host�˿�������ѹ��һ��micromap  ,��Ч��vkCmdCopyMicromapEXT
		vkCopyMicromapEXT(device, VkDeferredOperationKHR{/*��������һ����Ч��VkDeferredOperationKHR*/ }, & copyMicromapInfoEXT);
		/*
		vkCopyMicromapEXT��Ч�÷�:
		1.  VkPhysicalDeviceOpacityMicromapFeaturesEXT::micromapHostCommands ���Ա��뿪��
		2.�κ�deferredOperation������֮ǰ��deferred operation �����Ѿ����
		3.���ڴ���pInfo->src��pInfo->dst micromap��buffer�����Ѿ��󶨵�host-visible device memory�ϣ��Ҹ�memoryû����multiple instances�Ϸ���
		*/


		VkCopyMemoryToMicromapInfoEXT copyMemoryToMicromapInfoEXT{/*��������һ����Ч��VkCopyMemoryToMicromapInfoEXT*/ };//ǰ���Ѿ����������ﲻ�ٸ���
		//host�˿��� host accessible memory ��һ��micromap����Ч��vkCmdCopyMemoryToMicromapEXT�����Խ����� vkCmdCopyMicromapToMemoryEXT ����vkCopyMicromapToMemoryEXT������micromap
		vkCopyMemoryToMicromapEXT(device, VkDeferredOperationKHR{/*��������һ����Ч��VkDeferredOperationKHR*/ }, & copyMemoryToMicromapInfoEXT);
		/*
		vkCopyMemoryToMicromapEXT��Ч�÷�:
		1. VkPhysicalDeviceOpacityMicromapFeaturesEXT::micromapHostCommands ���Ա��뿪��
		2.�κ�deferredOperation������֮ǰ��deferred operation �����Ѿ����
		3.pInfo->src.hostAddress��������Ч�� host pointer�����������뵽16�ֽ�
		4.���ڴ���pInfo->dst micromap��buffer�����Ѿ��󶨵�host-visible device memory�ϣ��Ҹ�memoryû����multiple instances�Ϸ���

		*/


		VkCopyMicromapToMemoryInfoEXT copyMicromapToMemoryInfoEXT{/*��������һ����Ч��VkCopyMicromapToMemoryInfoEXT*/ };//ǰ���Ѿ����������ﲻ�ٸ���
		//host�˿���һ��micromap��host accessible memory����Ч��vkCmdCopyMicromapToMemoryEXT���ýӿ�������Ա�vkCmdCopyMemoryToMicromapEXT ���� vkCopyMemoryToMicromapEXTʹ��
		vkCopyMicromapToMemoryEXT(device, VkDeferredOperationKHR{/*��������һ����Ч��VkDeferredOperationKHR*/ }, & copyMicromapToMemoryInfoEXT);
		/*
		vkCopyMicromapToMemoryEXT��Ч�÷�:
		1.VkPhysicalDeviceOpacityMicromapFeaturesEXT::micromapHostCommands���Ա��뿪��
		2.�κ�deferredOperation������֮ǰ��deferred operation �����Ѿ����
		3.pInfo->dst.hostAddress��������Ч�� host pointer�����������뵽16�ֽ�
		4.���ڴ���pInfo->src micromap��buffer�����Ѿ��󶨵�host-visible device memory�ϣ��Ҹ�memoryû����multiple instances�Ϸ���
		*/



		uint32_t needSize = 0;
		//host�˲�ѯmicromap�Ĵ�С����
		VkMicromapEXT micromapEXT{/*��������һ����Ч��VkMicromapEXT*/ };
		//��Ч�� vkCmdWriteMicromapsPropertiesEXT
		vkWriteMicromapsPropertiesEXT(device, 1, &micromapEXT,
			VK_QUERY_TYPE_ACCELERATION_STRUCTURE_COMPACTED_SIZE_KHR/*queryType��ָ����ѯ����*/, sizeof(needSize)/*dataSize��pData�е��ֽڴ�С*/, &needSize/*pData,Ϊ�û���������ڴ�Ų�ѯ������ڴ�ָ��*/, sizeof(needSize)/*stride,ΪpData�е����Ĳ�ѯ���֮����ֽڲ���*/);
		/*
		vkWriteMicromapsPropertiesEXT��Ч�÷�:
		1.VkPhysicalDeviceOpacityMicromapFeaturesEXT::micromapHostCommands ���Ա��뿪��
		2.pMicromaps�е�����micromap�����Ѿ��ڸ������ִ��ǰ����
		3.pMicromaps�е�����micromap���queryTypeΪVK_QUERY_TYPE_MICROMAP_COMPACTED_SIZE_EXT�������VK_BUILD_MICROMAP_ALLOW_COMPACTION_BIT_EXT����
		4.queryType����ΪVK_QUERY_TYPE_MICROMAP_COMPACTED_SIZE_EXT ���� VK_QUERY_TYPE_MICROMAP_SERIALIZATION_SIZE_EXT
		5.���queryTypeΪVK_QUERY_TYPE_MICROMAP_SERIALIZATION_SIZE_EXT����1��stride ����ΪVkDeviceSize�����ֽڴ�С��������
																		  ��2��pData������һ��ָ��VkDeviceSize������
		6.dataSize ������ڻ����micromapCount*stride
		7.��������pMicromaps��ÿ��micromap��buffer�����Ѿ��󶨵�host-visible device memory�ϣ��Ҹ�memoryû����multiple instances�Ϸ���
		*/



		//Displacement Micromap �μ�p3324
		{
			//����� p3324 - p3327
		}

	}
}

void MicromapAndRayTraverseRayTracingTest::RayTraverseTest()
{
}

void MicromapAndRayTraverseRayTracingTest::RayTracingTest()
{
}

NS_TEST_END