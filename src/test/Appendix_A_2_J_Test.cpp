#include "Appendix_A_2_J_Test.h"
NS_TEST_BEGIN
Appendix_A_2_J_Test::Appendix_A_2_J_Test()
{
}

void Appendix_A_2_J_Test::run()
{
}

Appendix_A_2_J_Test::~Appendix_A_2_J_Test()
{
}

void Appendix_A_2_J_Test::Appendix_A_Test()//Vulkan Environment for SPIR-V
{
	//vulkan�й���shaders����ϸ����� Khronos SPIR-V Specification �Լ� Khronos SPIR-V Extended Instructions for GLSL Specification����Щ��������https://registry.khronos.org/spir-v/


	//Versions and Formats  ��p4228  ������SPIR-V��֧�ְ汾�͸�ʽ


	//Capabilities  ��p4228
	{
		/*
		����һ��֧�ֵ�SPIR - V capabilities����RayTracingNV�ȣ���p4228
		
		��Щ�о��ڱ��У���
		Table 96. List of SPIR-V Capabilities and corresponding Vulkan features, extensions, or core version  p4228



		*/

	}

	//SPIR-V Extensions  ��p4238
	{
		/*
		����һ��֧�ֵ�SPIR - V extensions����SPV_KHR_variable_pointers�ȣ���p4238

		��Щ�о��ڱ��У���
		Table 97. List of SPIR-V Extensions and corresponding Vulkan extensions or core version   p4238



		*/

	}


	//Validation Rules Within a Module  �μ�p4243
	{
		//�����˴���SPIR-Vģ����Ҫ����Ĺ������£�

		//Standalone SPIR-V Validation  �μ�p4243 - p4253

		//Runtime SPIR-V Validation  �μ�p4254 - p4273

	}

	//Precision and Operation of SPIR-V Instructions  �μ�p4274   �� ������SPIR-Vָ��ľ��ȺͲ���

	//Signedness of SPIR-V Image Accesses  �μ�p4279  ��������SPIR-Vͼ����ʵķ�����

	//Image Format and Type Matching  �μ�p4280  �������˷���ͼ������е�ͼ���ʽ������ƥ��

	//Compatibility Between SPIR-V Image Formats and Vulkan Formats  �μ�p4282  ��������SPIR-Vͼ���ʽ��Vulkanͼ���ʽ�ļ����ԣ���Table 100. SPIR-V and Vulkan Image Format Compatibility

	//Ray Query Precision and Operation  �μ�p4283 ��

}

void Appendix_A_2_J_Test::Appendix_B_Test()//Memory Model
{
	//Memory Model ����������ʵ���ṩ��ͬ�����ƣ���Ҫ������:


	//Agent   �μ�p4285

	//Memory Location  �μ�p4285

	//Allocation  �μ�p4285


	//Memory Operation  �μ�p4286

	//Reference  �μ�p4286

	//Program-Order  �μ�p4286

	//Shader Call Related  �μ�p4287

	//Shader Call Order  �μ�p4287

	//Scope  �μ�p4287

	//Atomic Operation  �μ�p4288

	//Scoped Modification Order   �μ�p4288

	//Memory Semantics  �μ�p4289

	//Release Sequence  �μ�p4290

	//Synchronizes-With  �μ�p4291

	//System-Synchronizes-With  �μ�p4293

	//Private vs. Non-Private  �μ�p4293

	//Inter-Thread-Happens-Before  �μ�p4294

	//Happens-Before  �μ�p4294

	//Availability and Visibility  �μ�p4295

	//Availability, Visibility, and Domain Operations  �μ�p4296

	//Availability and Visibility Semantics  �μ�p4297

	//Per-Instruction Availability and Visibility Semantics  �μ�p4298

	//Location-Ordered  �μ�p4299

	//Data Race  �μ�p4299

	//Visible-To  �μ�p4300

	//Acyclicity  �μ�p4300

	//Shader I/O  �μ�p4301

	//Deallocation  �μ�p4301

	//Descriptions (Informative)  �μ�p4302 

	//Tessellation Output Ordering  �μ�p4302

	//Cooperative Matrix Memory Access   �μ�p4302

}

void Appendix_A_2_J_Test::Appendix_C_Test()//Compressed Image Formats
{
	//Compressed Image Formats ������Vulkan֧�ֵ�ѹ��ͼ���ʽ����Ҫ�����У�

	//Block-Compressed Image Formats  �μ�p4303  ��������"BC"��VkFormat�� ������������Table 101. Mapping of Vulkan BC formats to descriptions

	//ETC Compressed Image Formats  �μ�p4306  ��������"ETC2"�Լ�"EAC"��VkFormat�� ������������Table 102. Mapping of Vulkan ETC formats to descriptions

	//ASTC Compressed Image Formats  �μ�p4307  ��������"ASTC"��VkFormat�� ������������Table 103. Mapping of Vulkan ASTC formats to descriptions

	//PVRTC Compressed Image Formats  �μ�p4310  ��������"PVRTC"��VkFormat�� ������������Table 104. Mapping of Vulkan PVRTC formats to descriptions
}

void Appendix_A_2_J_Test::Appendix_D_Test()//Core Revisions (Informative)
{
	//Core Revisions (Informative) ������Vulkan API�汾�ĸ�����Ϣ����Ҫ�����У�

	//Version 1.3  �μ�p4311 - p4320  ��������Vulkan 1.3�汾�ĸ�������

	//Version 1.2  �μ�p4320 - p4328  ��������Vulkan 1.2�汾�ĸ�������

	//Version 1.1  �μ�p4328 - p4340  ��������Vulkan 1.1�汾�ĸ�������

	//Version 1.0  �μ�p4340 - p4353  ��������Vulkan 1.0�汾�ķ�������
}

void Appendix_A_2_J_Test::Appendix_E_Test()//Layers & Extensions (Informative)
{
	//Layers & Extensions (Informative) ������һ��vulkan extensions�������Ϣ�� ������ע���vulkan extensions���Լ�https://registry.khronos.org/vulkan/��extensions��Khronos�����������ִ�KHR�����������̷����Ĵ�EXT����Ҫ�����У�

	//Extension Dependencies  �μ�p4354  ��������Vulkan��չ������Ҫ�ض��İ汾����������չ֧��

	//Extension Interactions  �μ�p4355  ��������һЩVulkan��չ����Ľӿ���Ҫ������������չ

	//List of Current Extensions  �μ�p4355  ���оٵ�ǰ��Vulkan��չ,���ڰ汾1.3.285
	{
		/*
        ��չ:
        VK_KHR_acceleration_structure  :  ��չ����������Ľӿڻ������ݽṹ�������p4363
        VK_KHR_android_surface  :  ��չ����������Ľӿڻ������ݽṹ�������p4378
        VK_KHR_calibrated_timestamps  :  ��չ����������Ľӿڻ������ݽṹ�������p4380
        VK_KHR_cooperative_matrix  :  ��չ����������Ľӿڻ������ݽṹ�������p4382
        VK_KHR_deferred_host_operations  :  ��չ����������Ľӿڻ������ݽṹ�������p4384
        VK_KHR_display  :  ��չ����������Ľӿڻ������ݽṹ�������p4389
        VK_KHR_display_swapchain  :  ��չ����������Ľӿڻ������ݽṹ�������p4396
        VK_KHR_dynamic_rendering_local_read  :  ��չ����������Ľӿڻ������ݽṹ�������p4399
        VK_KHR_external_fence_fd  :  ��չ����������Ľӿڻ������ݽṹ�������p4401
        VK_KHR_external_fence_win32  :  ��չ����������Ľӿڻ������ݽṹ�������p4403
        VK_KHR_external_memory_fd  :  ��չ����������Ľӿڻ������ݽṹ�������p4405
        VK_KHR_external_memory_win32  :  ��չ����������Ľӿڻ������ݽṹ�������p4407
        VK_KHR_external_semaphore_fd  :  ��չ����������Ľӿڻ������ݽṹ�������p4409
        VK_KHR_external_semaphore_win32  :  ��չ����������Ľӿڻ������ݽṹ�������p4411
        VK_KHR_fragment_shader_barycentric  :  ��չ����������Ľӿڻ������ݽṹ�������p4413
        VK_KHR_fragment_shading_rate  :  ��չ����������Ľӿڻ������ݽṹ�������p4416
        VK_KHR_get_display_properties2  :  ��չ����������Ľӿڻ������ݽṹ�������p4419
        VK_KHR_get_surface_capabilities2  :  ��չ����������Ľӿڻ������ݽṹ�������p4421
        VK_KHR_global_priority  :  ��չ����������Ľӿڻ������ݽṹ�������p4423
        VK_KHR_incremental_present  :  ��չ����������Ľӿڻ������ݽṹ�������p4425
        VK_KHR_index_type_uint8  :  ��չ����������Ľӿڻ������ݽṹ�������p4428
        VK_KHR_line_rasterization  :  ��չ����������Ľӿڻ������ݽṹ�������p4429
        VK_KHR_load_store_op_none  :  ��չ����������Ľӿڻ������ݽṹ�������p4431
        VK_KHR_maintenance5  :  ��չ����������Ľӿڻ������ݽṹ�������p4432
        VK_KHR_maintenance6  :  ��չ����������Ľӿڻ������ݽṹ�������p4439
        VK_KHR_map_memory2  :  ��չ����������Ľӿڻ������ݽṹ�������p4442
        VK_KHR_performance_query  :  ��չ����������Ľӿڻ������ݽṹ�������p4444
        VK_KHR_pipeline_executable_properties  :  ��չ����������Ľӿڻ������ݽṹ�������p4452
        VK_KHR_pipeline_library  :  ��չ����������Ľӿڻ������ݽṹ�������p4454
        VK_KHR_portability_enumeration  :  ��չ����������Ľӿڻ������ݽṹ�������p4456
        VK_KHR_present_id  :  ��չ����������Ľӿڻ������ݽṹ�������p4457
        VK_KHR_present_wait  :  ��չ����������Ľӿڻ������ݽṹ�������p4458
        VK_KHR_push_descriptor  :  ��չ����������Ľӿڻ������ݽṹ�������p4461
        VK_KHR_ray_query  :  ��չ����������Ľӿڻ������ݽṹ�������p4463
        VK_KHR_ray_tracing_maintenance1  :  ��չ����������Ľӿڻ������ݽṹ�������p4466
        VK_KHR_ray_tracing_pipeline  :  ��չ����������Ľӿڻ������ݽṹ�������p4469
        VK_KHR_ray_tracing_position_fetch  :  ��չ����������Ľӿڻ������ݽṹ�������p4479
        VK_KHR_shader_clock  :  ��չ����������Ľӿڻ������ݽṹ�������p4481
        VK_KHR_shader_expect_assume  :  ��չ����������Ľӿڻ������ݽṹ�������p4482
        VK_KHR_shader_float_controls2  :  ��չ����������Ľӿڻ������ݽṹ�������p4484
        VK_KHR_shader_maximal_reconvergence  :  ��չ����������Ľӿڻ������ݽṹ�������p4485
        VK_KHR_shader_quad_control  :  ��չ����������Ľӿڻ������ݽṹ�������p4487
        VK_KHR_shader_subgroup_rotate  :  ��չ����������Ľӿڻ������ݽṹ�������p4489
        VK_KHR_shader_subgroup_uniform_control_flow  :  ��չ����������Ľӿڻ������ݽṹ�������p4490
        VK_KHR_shared_presentable_image  :  ��չ����������Ľӿڻ������ݽṹ�������p4492
        VK_KHR_surface  :  ��չ����������Ľӿڻ������ݽṹ�������p4495
        VK_KHR_surface_protected_capabilities  :  ��չ����������Ľӿڻ������ݽṹ�������p4500
        VK_KHR_swapchain  :  ��չ����������Ľӿڻ������ݽṹ�������p4502
        VK_KHR_swapchain_mutable_format  :  ��չ����������Ľӿڻ������ݽṹ�������p4517
        VK_KHR_vertex_attribute_divisor  :  ��չ����������Ľӿڻ������ݽṹ�������p4519
        VK_KHR_video_decode_av1  :  ��չ����������Ľӿڻ������ݽṹ�������p4521
        VK_KHR_video_decode_h264  :  ��չ����������Ľӿڻ������ݽṹ�������p4523
        VK_KHR_video_decode_h265  :  ��չ����������Ľӿڻ������ݽṹ�������p4526
        VK_KHR_video_decode_queue  :  ��չ����������Ľӿڻ������ݽṹ�������p4529
        VK_KHR_video_encode_h264  :  ��չ����������Ľӿڻ������ݽṹ�������p4532
        VK_KHR_video_encode_h265  :  ��չ����������Ľӿڻ������ݽṹ�������p4538
        VK_KHR_video_encode_queue  :  ��չ����������Ľӿڻ������ݽṹ�������p4544
        VK_KHR_video_maintenance1  :  ��չ����������Ľӿڻ������ݽṹ�������p4550
        VK_KHR_video_queue  :  ��չ����������Ľӿڻ������ݽṹ�������p4522
        VK_KHR_wayland_surface  :  ��չ����������Ľӿڻ������ݽṹ�������p4558
        VK_KHR_win32_keyed_mutex  :  ��չ����������Ľӿڻ������ݽṹ�������p4561
        VK_KHR_win32_surface  :  ��չ����������Ľӿڻ������ݽṹ�������p4562
        VK_KHR_workgroup_memory_explicit_layout  :  ��չ����������Ľӿڻ������ݽṹ�������p4565
        VK_KHR_xcb_surface  :  ��չ����������Ľӿڻ������ݽṹ�������p4566
        VK_KHR_xlib_surface  :  ��չ����������Ľӿڻ������ݽṹ�������p4569
        VK_EXT_acquire_drm_display  :  ��չ����������Ľӿڻ������ݽṹ�������p4571
        VK_EXT_acquire_xlib_display  :  ��չ����������Ľӿڻ������ݽṹ�������p4573
        VK_EXT_astc_decode_mode  :  ��չ����������Ľӿڻ������ݽṹ�������p4574
        VK_EXT_attachment_feedback_loop_dynamic_state  :  ��չ����������Ľӿڻ������ݽṹ�������p4577
        VK_EXT_attachment_feedback_loop_layout  :  ��չ����������Ľӿڻ������ݽṹ�������p4578
        VK_EXT_blend_operation_advanced  :  ��չ����������Ľӿڻ������ݽṹ�������p4580
        VK_EXT_border_color_swizzle  :  ��չ����������Ľӿڻ������ݽṹ�������p4584
        VK_EXT_color_write_enable  :  ��չ����������Ľӿڻ������ݽṹ�������p4586
        VK_EXT_conditional_rendering  :  ��չ����������Ľӿڻ������ݽṹ�������p4588
        VK_EXT_conservative_rasterization  :  ��չ����������Ľӿڻ������ݽṹ�������p4590
        VK_EXT_custom_border_color  :  ��չ����������Ľӿڻ������ݽṹ�������p4592
        VK_EXT_debug_utils  :  ��չ����������Ľӿڻ������ݽṹ�������p4596
        VK_EXT_depth_bias_control  :  ��չ����������Ľӿڻ������ݽṹ�������p4605
        VK_EXT_depth_clamp_zero_one  :  ��չ����������Ľӿڻ������ݽṹ�������p4607
        VK_EXT_depth_clip_control  :  ��չ����������Ľӿڻ������ݽṹ�������p4608
        VK_EXT_depth_clip_enable  :  ��չ����������Ľӿڻ������ݽṹ�������p4640
        VK_EXT_depth_range_unrestricted  :  ��չ����������Ľӿڻ������ݽṹ�������p4611
        VK_EXT_descriptor_buffer  :  ��չ����������Ľӿڻ������ݽṹ�������p4613
        VK_EXT_device_address_binding_report  :  ��չ����������Ľӿڻ������ݽṹ�������p4617
        VK_EXT_device_fault  :  ��չ����������Ľӿڻ������ݽṹ�������p4620
        VK_EXT_device_memory_report  :  ��չ����������Ľӿڻ������ݽṹ�������p4622
        VK_EXT_direct_mode_display  :  ��չ����������Ľӿڻ������ݽṹ�������p4626
        VK_EXT_directfb_surface  :  ��չ����������Ľӿڻ������ݽṹ�������p4628
        VK_EXT_discard_rectangles  :  ��չ����������Ľӿڻ������ݽṹ�������p4629
        VK_EXT_display_control  :  ��չ����������Ľӿڻ������ݽṹ�������p4631
        VK_EXT_display_surface_counter  :  ��չ����������Ľӿڻ������ݽṹ�������p4633
        VK_EXT_dynamic_rendering_unused_attachments  :  ��չ����������Ľӿڻ������ݽṹ�������p4635
        VK_EXT_extended_dynamic_state3  :  ��չ����������Ľӿڻ������ݽṹ�������p4636
        VK_EXT_external_memory_acquire_unmodified  :  ��չ����������Ľӿڻ������ݽṹ�������p4643
        VK_EXT_external_memory_dma_buf  :  ��չ����������Ľӿڻ������ݽṹ�������p4644
        VK_EXT_external_memory_host  :  ��չ����������Ľӿڻ������ݽṹ�������p4646
        VK_EXT_filter_cubic  :  ��չ����������Ľӿڻ������ݽṹ�������p4648
        VK_EXT_fragment_density_map  :  ��չ����������Ľӿڻ������ݽṹ�������p4650
        VK_EXT_fragment_density_map2  :  ��չ����������Ľӿڻ������ݽṹ�������p4653
        VK_EXT_fragment_shader_interlock  :  ��չ����������Ľӿڻ������ݽṹ�������p4654
        VK_EXT_frame_boundary  :  ��չ����������Ľӿڻ������ݽṹ�������p4656
        VK_EXT_full_screen_exclusive  :  ��չ����������Ľӿڻ������ݽṹ�������p4658
        VK_EXT_graphics_pipeline_library  :  ��չ����������Ľӿڻ������ݽṹ�������p4662
        VK_EXT_hdr_metadata  :  ��չ����������Ľӿڻ������ݽṹ�������p4664
        VK_EXT_headless_surface  :  ��չ����������Ľӿڻ������ݽṹ�������p4666
        VK_EXT_host_image_copy  :  ��չ����������Ľӿڻ������ݽṹ�������p4667
        VK_EXT_image_2d_view_of_3d  :  ��չ����������Ľӿڻ������ݽṹ�������p4671
        VK_EXT_image_compression_control  :  ��չ����������Ľӿڻ������ݽṹ�������p4672
        VK_EXT_image_compression_control_swapchain  :  ��չ����������Ľӿڻ������ݽṹ�������p4675
        VK_EXT_image_drm_format_modifier  :  ��չ����������Ľӿڻ������ݽṹ�������p4676
        VK_EXT_image_sliced_view_of_3d  :  ��չ����������Ľӿڻ������ݽṹ�������p4684
        VK_EXT_image_view_min_lod  :  ��չ����������Ľӿڻ������ݽṹ�������p4685
        VK_EXT_layer_settings  :  ��չ����������Ľӿڻ������ݽṹ�������p4687
        VK_EXT_legacy_dithering  :  ��չ����������Ľӿڻ������ݽṹ�������p4690
        VK_EXT_legacy_vertex_attributes  :  ��չ����������Ľӿڻ������ݽṹ�������p4692
        VK_EXT_map_memory_placed  :  ��չ����������Ľӿڻ������ݽṹ�������p4694
        VK_EXT_memory_budget  :  ��չ����������Ľӿڻ������ݽṹ�������p4695
        VK_EXT_memory_priority  :  ��չ����������Ľӿڻ������ݽṹ�������p4697
        VK_EXT_mesh_shader  :  ��չ����������Ľӿڻ������ݽṹ�������p4698
        VK_EXT_metal_objects  :  ��չ����������Ľӿڻ������ݽṹ�������p4702
        VK_EXT_metal_surface  :  ��չ����������Ľӿڻ������ݽṹ�������p4705
        VK_EXT_multi_draw  :  ��չ����������Ľӿڻ������ݽṹ�������p4706
        VK_EXT_multisampled_render_to_single_sampled  :  ��չ����������Ľӿڻ������ݽṹ�������p4708
        VK_EXT_mutable_descriptor_type  :  ��չ����������Ľӿڻ������ݽṹ�������p4710
        VK_EXT_nested_command_buffer  :  ��չ����������Ľӿڻ������ݽṹ�������p4712
        VK_EXT_non_seamless_cube_map  :  ��չ����������Ľӿڻ������ݽṹ�������p4714
        VK_EXT_opacity_micromap  :  ��չ����������Ľӿڻ������ݽṹ�������p4716
        VK_EXT_pageable_device_local_memory  :  ��չ����������Ľӿڻ������ݽṹ�������p4721
        VK_EXT_pci_bus_info  :  ��չ����������Ľӿڻ������ݽṹ�������p4723
        VK_EXT_physical_device_drm  :  ��չ����������Ľӿڻ������ݽṹ�������p4725
        VK_EXT_pipeline_library_group_handles  :  ��չ����������Ľӿڻ������ݽṹ�������p4726
        VK_EXT_pipeline_properties  :  ��չ����������Ľӿڻ������ݽṹ�������p4728
        VK_EXT_pipeline_protected_access  :  ��չ����������Ľӿڻ������ݽṹ�������p4730
        VK_EXT_pipeline_robustness  :  ��չ����������Ľӿڻ������ݽṹ�������p4732
        VK_EXT_post_depth_coverage  :  ��չ����������Ľӿڻ������ݽṹ�������p4734
        VK_EXT_primitive_topology_list_restart  :  ��չ����������Ľӿڻ������ݽṹ�������p4735
        VK_EXT_primitives_generated_query  :  ��չ����������Ľӿڻ������ݽṹ�������p4737
        VK_EXT_provoking_vertex  :  ��չ����������Ľӿڻ������ݽṹ�������p4739
        VK_EXT_queue_family_foreign  :  ��չ����������Ľӿڻ������ݽṹ�������p4741
        VK_EXT_rasterization_order_attachment_access  :  ��չ����������Ľӿڻ������ݽṹ�������p4743
        VK_EXT_rgba10x6_formats  :  ��չ����������Ľӿڻ������ݽṹ�������p4745
        VK_EXT_robustness2  :  ��չ����������Ľӿڻ������ݽṹ�������p4746
        VK_EXT_sample_locations  :  ��չ����������Ľӿڻ������ݽṹ�������p4748
        VK_EXT_shader_atomic_float  :  ��չ����������Ľӿڻ������ݽṹ�������p4750
        VK_EXT_shader_atomic_float2  :  ��չ����������Ľӿڻ������ݽṹ�������p4752
        VK_EXT_shader_image_atomic_int64  :  ��չ����������Ľӿڻ������ݽṹ�������p4754
        VK_EXT_shader_module_identifier  :  ��չ����������Ľӿڻ������ݽṹ�������p4755
        VK_EXT_shader_object  :  ��չ����������Ľӿڻ������ݽṹ�������p4758
        VK_EXT_shader_stencil_export  :  ��չ����������Ľӿڻ������ݽṹ�������p4770
        VK_EXT_shader_tile_image  :  ��չ����������Ľӿڻ������ݽṹ�������p4771
        VK_EXT_subpass_merge_feedback  :  ��չ����������Ľӿڻ������ݽṹ�������p4774
        VK_EXT_surface_maintenance1  :  ��չ����������Ľӿڻ������ݽṹ�������p4775
        VK_EXT_swapchain_colorspace  :  ��չ����������Ľӿڻ������ݽṹ�������p4777
        VK_EXT_swapchain_maintenance1  :  ��չ����������Ľӿڻ������ݽṹ�������p4780
        VK_EXT_transform_feedback  :  ��չ����������Ľӿڻ������ݽṹ�������p4782
        VK_EXT_validation_cache  :  ��չ����������Ľӿڻ������ݽṹ�������p4785
        VK_EXT_vertex_input_dynamic_state  :  ��չ����������Ľӿڻ������ݽṹ�������p4787
        VK_EXT_ycbcr_image_arrays  :  ��չ����������Ľӿڻ������ݽṹ�������p4789
        VK_AMD_buffer_marker  :  ��չ����������Ľӿڻ������ݽṹ�������p4790
        VK_AMD_device_coherent_memory  :  ��չ����������Ľӿڻ������ݽṹ�������p4791
        VK_AMD_display_native_hdr  :  ��չ����������Ľӿڻ������ݽṹ�������p4793
        VK_AMD_gcn_shader  :  ��չ����������Ľӿڻ������ݽṹ�������p4795
        VK_AMD_memory_overallocation_behavior  :  ��չ����������Ľӿڻ������ݽṹ�������p4796
        VK_AMD_mixed_attachment_samples  :  ��չ����������Ľӿڻ������ݽṹ�������p4797
        VK_AMD_pipeline_compiler_control  :  ��չ����������Ľӿڻ������ݽṹ�������p4799
        VK_AMD_rasterization_order  :  ��չ����������Ľӿڻ������ݽṹ�������p4800
        VK_AMD_shader_ballot  :  ��չ����������Ľӿڻ������ݽṹ�������p4803
        VK_AMD_shader_core_properties  :  ��չ����������Ľӿڻ������ݽṹ�������p4804
        VK_AMD_shader_core_properties2  :  ��չ����������Ľӿڻ������ݽṹ�������p4807
        VK_AMD_shader_early_and_late_fragment_tests  :  ��չ����������Ľӿڻ������ݽṹ�������p4808
        VK_AMD_shader_explicit_vertex_parameter  :  ��չ����������Ľӿڻ������ݽṹ�������p4810
        VK_AMD_shader_fragment_mask  :  ��չ����������Ľӿڻ������ݽṹ�������p4811
        VK_AMD_shader_image_load_store_lod  :  ��չ����������Ľӿڻ������ݽṹ�������p4813
        VK_AMD_shader_info  :  ��չ����������Ľӿڻ������ݽṹ�������p4814
        VK_AMD_shader_trinary_minmax  :  ��չ����������Ľӿڻ������ݽṹ�������p4817
        VK_AMD_texture_gather_bias_lod  :  ��չ����������Ľӿڻ������ݽṹ�������p4818
        VK_ANDROID_external_format_resolve  :  ��չ����������Ľӿڻ������ݽṹ�������p4821
        VK_ANDROID_external_memory_android_hardware_buffer  :  ��չ����������Ľӿڻ������ݽṹ�������p4823
        VK_ARM_render_pass_striped  :  ��չ����������Ľӿڻ������ݽṹ�������p4827
        VK_ARM_scheduling_controls  :  ��չ����������Ľӿڻ������ݽṹ�������p4829
        VK_ARM_shader_core_builtins  :  ��չ����������Ľӿڻ������ݽṹ�������p4831
        VK_ARM_shader_core_properties  :  ��չ����������Ľӿڻ������ݽṹ�������p4832
        VK_FUCHSIA_buffer_collection  :  ��չ����������Ľӿڻ������ݽṹ�������p4834
        VK_FUCHSIA_external_memory  :  ��չ����������Ľӿڻ������ݽṹ�������p4837
        VK_FUCHSIA_external_semaphore  :  ��չ����������Ľӿڻ������ݽṹ�������p4839
        VK_FUCHSIA_imagepipe_surface  :  ��չ����������Ľӿڻ������ݽṹ�������p4840
        VK_GGP_frame_token  :  ��չ����������Ľӿڻ������ݽṹ�������p4842
        VK_GGP_stream_descriptor_surface  :  ��չ����������Ľӿڻ������ݽṹ�������p4843
        VK_GOOGLE_decorate_string  :  ��չ����������Ľӿڻ������ݽṹ�������p4845
        VK_GOOGLE_display_timing  :  ��չ����������Ľӿڻ������ݽṹ�������p4846
        VK_GOOGLE_hlsl_functionality1  :  ��չ����������Ľӿڻ������ݽṹ�������p4848
        VK_GOOGLE_surfaceless_query  :  ��չ����������Ľӿڻ������ݽṹ�������p4849
        VK_GOOGLE_user_type  :  ��չ����������Ľӿڻ������ݽṹ�������p4850
        VK_HUAWEI_cluster_culling_shader  :  ��չ����������Ľӿڻ������ݽṹ�������p4851
        VK_HUAWEI_invocation_mask  :  ��չ����������Ľӿڻ������ݽṹ�������p4857
        VK_HUAWEI_subpass_shading  :  ��չ����������Ľӿڻ������ݽṹ�������p4860
        VK_IMG_filter_cubic  :  ��չ����������Ľӿڻ������ݽṹ�������p4867
        VK_IMG_relaxed_line_rasterization  :  ��չ����������Ľӿڻ������ݽṹ�������p4868
        VK_INTEL_performance_query  :  ��չ����������Ľӿڻ������ݽṹ�������p4870
        VK_INTEL_shader_integer_functions2  :  ��չ����������Ľӿڻ������ݽṹ�������p4875
        VK_LUNARG_direct_driver_loading  :  ��չ����������Ľӿڻ������ݽṹ�������p4876
        VK_MESA_image_alignment_control  :  ��չ����������Ľӿڻ������ݽṹ�������p4878
        VK_MSFT_layered_driver  :  ��չ����������Ľӿڻ������ݽṹ�������p4880
        VK_NN_vi_surface  :  ��չ����������Ľӿڻ������ݽṹ�������p4881
        VK_NV_acquire_winrt_display  :  ��չ����������Ľӿڻ������ݽṹ�������p4883
        VK_NV_clip_space_w_scaling  :  ��չ����������Ľӿڻ������ݽṹ�������p4885
        VK_NV_compute_shader_derivatives  :  ��չ����������Ľӿڻ������ݽṹ�������p4889
        VK_NV_cooperative_matrix  :  ��չ����������Ľӿڻ������ݽṹ�������p4891
        VK_NV_copy_memory_indirect  :  ��չ����������Ľӿڻ������ݽṹ�������p4893
        VK_NV_corner_sampled_image  :  ��չ����������Ľӿڻ������ݽṹ�������p4895
        VK_NV_coverage_reduction_mode  :  ��չ����������Ľӿڻ������ݽṹ�������p4897
        VK_NV_dedicated_allocation_image_aliasing  :  ��չ����������Ľӿڻ������ݽṹ�������p4899
        VK_NV_descriptor_pool_overallocation  :  ��չ����������Ľӿڻ������ݽṹ�������p4901
        VK_NV_device_diagnostic_checkpoints  :  ��չ����������Ľӿڻ������ݽṹ�������p4902
        VK_NV_device_diagnostics_config  :  ��չ����������Ľӿڻ������ݽṹ�������p4904
        VK_NV_device_generated_commands  :  ��չ����������Ľӿڻ������ݽṹ�������p4905
        VK_NV_device_generated_commands_compute  :  ��չ����������Ľӿڻ������ݽṹ�������p4913
        VK_NV_extended_sparse_address_space  :  ��չ����������Ľӿڻ������ݽṹ�������p4915
        VK_NV_external_memory_rdma  :  ��չ����������Ľӿڻ������ݽṹ�������p4916
        VK_NV_fill_rectangle  :  ��չ����������Ľӿڻ������ݽṹ�������p4920
        VK_NV_fragment_coverage_to_color  :  ��չ����������Ľӿڻ������ݽṹ�������p4921
        VK_NV_fragment_shading_rate_enums  :  ��չ����������Ľӿڻ������ݽṹ�������p4922
        VK_NV_framebuffer_mixed_samples  :  ��չ����������Ľӿڻ������ݽṹ�������p4925
        VK_NV_geometry_shader_passthrough  :  ��չ����������Ľӿڻ������ݽṹ�������p4927
        VK_NV_inherited_viewport_scissor  :  ��չ����������Ľӿڻ������ݽṹ�������p4930
        VK_NV_linear_color_attachment  :  ��չ����������Ľӿڻ������ݽṹ�������p4932
        VK_NV_low_latency  :  ��չ����������Ľӿڻ������ݽṹ�������p4934
        VK_NV_low_latency2  :  ��չ����������Ľӿڻ������ݽṹ�������p4934
        VK_NV_memory_decompression  :  ��չ����������Ľӿڻ������ݽṹ�������p4937
        VK_NV_mesh_shader  :  ��չ����������Ľӿڻ������ݽṹ�������p4939
        VK_NV_optical_flow  :  ��չ����������Ľӿڻ������ݽṹ�������p4943
        VK_NV_per_stage_descriptor_set  :  ��չ����������Ľӿڻ������ݽṹ�������p4948
        VK_NV_present_barrier  :  ��չ����������Ľӿڻ������ݽṹ�������p4949
        VK_NV_raw_access_chains  :  ��չ����������Ľӿڻ������ݽṹ�������p4951
        VK_NV_ray_tracing  :  ��չ����������Ľӿڻ������ݽṹ�������p4952
        VK_NV_ray_tracing_invocation_reorder  :  ��չ����������Ľӿڻ������ݽṹ�������p4959
        VK_NV_ray_tracing_motion_blur  :  ��չ����������Ľӿڻ������ݽṹ�������p4963
        VK_NV_ray_tracing_validation  :  ��չ����������Ľӿڻ������ݽṹ�������p4966
        VK_NV_representative_fragment_test  :  ��չ����������Ľӿڻ������ݽṹ�������p4967
        VK_NV_sample_mask_override_coverage  :  ��չ����������Ľӿڻ������ݽṹ�������p4969
        VK_NV_scissor_exclusive  :  ��չ����������Ľӿڻ������ݽṹ�������p4971
        VK_NV_shader_atomic_float16_vector  :  ��չ����������Ľӿڻ������ݽṹ�������p4973
        VK_NV_shader_image_footprint  :  ��չ����������Ľӿڻ������ݽṹ�������p4974
        VK_NV_shader_sm_builtins  :  ��չ����������Ľӿڻ������ݽṹ�������p4979
        VK_NV_shader_subgroup_partitioned  :  ��չ����������Ľӿڻ������ݽṹ�������p4981
        VK_NV_shading_rate_image  :  ��չ����������Ľӿڻ������ݽṹ�������p4982
        VK_NV_viewport_array2  :  ��չ����������Ľӿڻ������ݽṹ�������p4986
        VK_NV_viewport_swizzle  :  ��չ����������Ľӿڻ������ݽṹ�������p4988
        VK_NVX_binary_import  :  ��չ����������Ľӿڻ������ݽṹ�������p4992
        VK_NVX_image_view_handle  :  ��չ����������Ľӿڻ������ݽṹ�������p5000
        VK_NVX_multiview_per_view_attributes  :  ��չ����������Ľӿڻ������ݽṹ�������p5001
        VK_QCOM_filter_cubic_clamp  :  ��չ����������Ľӿڻ������ݽṹ�������p5003
        VK_QCOM_filter_cubic_weights  :  ��չ����������Ľӿڻ������ݽṹ�������p5005
        VK_QCOM_fragment_density_map_offset  :  ��չ����������Ľӿڻ������ݽṹ�������p5007
        VK_QCOM_image_processing  :  ��չ����������Ľӿڻ������ݽṹ�������p5008
        VK_QCOM_image_processing2  :  ��չ����������Ľӿڻ������ݽṹ�������p5011
        VK_QCOM_multiview_per_view_render_areas  :  ��չ����������Ľӿڻ������ݽṹ�������p5014
        VK_QCOM_multiview_per_view_viewports  :  ��չ����������Ľӿڻ������ݽṹ�������p5016
        VK_QCOM_render_pass_shader_resolve  :  ��չ����������Ľӿڻ������ݽṹ�������p5018
        VK_QCOM_render_pass_store_ops  :  ��չ����������Ľӿڻ������ݽṹ�������p5021
        VK_QCOM_render_pass_transform  :  ��չ����������Ľӿڻ������ݽṹ�������p5022
        VK_QCOM_rotated_copy_commands  :  ��չ����������Ľӿڻ������ݽṹ�������p5026
        VK_QCOM_tile_properties  :  ��չ����������Ľӿڻ������ݽṹ�������p5028
        VK_QCOM_ycbcr_degamma  :  ��չ����������Ľӿڻ������ݽṹ�������p5030
        VK_QNX_external_memory_screen_buffer  :  ��չ����������Ľӿڻ������ݽṹ�������p5032
        VK_QNX_screen_surface  :  ��չ����������Ľӿڻ������ݽṹ�������p5034
        VK_SEC_amigo_profiling  :  ��չ����������Ľӿڻ������ݽṹ�������p5035
        VK_VALVE_descriptor_set_host_mapping  :  ��չ����������Ľӿڻ������ݽṹ�������p5038

        */
    }

    //List of Provisional Extensions  �μ�p5042  ���о���ʱ����չ,���ڰ汾1.3.285
    {
        /*
        ��չ:
        VK_KHR_portability_subset  :  ��չ����������Ľӿڻ������ݽṹ�������p5053
        VK_AMDX_shader_enqueue  :  ��չ����������Ľӿڻ������ݽṹ�������p5045
        VK_NV_cuda_kernel_launch  :  ��չ����������Ľӿڻ������ݽṹ�������p5048
        VK_NV_displacement_micromap  :  ��չ����������Ľӿڻ������ݽṹ�������p5050
        
        */

    }

	//List of Deprecated Extensions  �μ�p5052  ���о��ѷ�������չ,���ڰ汾1.3.285
    {
        /*
        ��չ:
        VK_KHR_16bit_storage  :  ��չ����������Ľӿڻ������ݽṹ�������p5057
        VK_KHR_8bit_storage  :  ��չ����������Ľӿڻ������ݽṹ�������p5058
        VK_KHR_bind_memory2  :  ��չ����������Ľӿڻ������ݽṹ�������p5059
        VK_KHR_buffer_device_address  :  ��չ����������Ľӿڻ������ݽṹ�������p5061
        VK_KHR_copy_commands2  :  ��չ����������Ľӿڻ������ݽṹ�������p5064
        VK_KHR_create_renderpass2  :  ��չ����������Ľӿڻ������ݽṹ�������p5066
        VK_KHR_dedicated_allocation  :  ��չ����������Ľӿڻ������ݽṹ�������p5068
        VK_KHR_depth_stencil_resolve  :  ��չ����������Ľӿڻ������ݽṹ�������p5072
        VK_KHR_descriptor_update_template  :  ��չ����������Ľӿڻ������ݽṹ�������p5074
        VK_KHR_device_group  :  ��չ����������Ľӿڻ������ݽṹ�������p5077
        VK_KHR_device_group_creation  :  ��չ����������Ľӿڻ������ݽṹ�������p5082
        VK_KHR_draw_indirect_count  :  ��չ����������Ľӿڻ������ݽṹ�������p5084
        VK_KHR_driver_properties  :  ��չ����������Ľӿڻ������ݽṹ�������p5085
        VK_KHR_dynamic_rendering  :  ��չ����������Ľӿڻ������ݽṹ�������p5087
        VK_KHR_external_fence  :  ��չ����������Ľӿڻ������ݽṹ�������p5091
        VK_KHR_external_fence_capabilities  :  ��չ����������Ľӿڻ������ݽṹ�������p5093
        VK_KHR_external_memory  :  ��չ����������Ľӿڻ������ݽṹ�������p5095
        VK_KHR_external_memory_capabilities  :  ��չ����������Ľӿڻ������ݽṹ�������p5100
        VK_KHR_external_semaphore  :  ��չ����������Ľӿڻ������ݽṹ�������p5104
        VK_KHR_external_semaphore_capabilities  :  ��չ����������Ľӿڻ������ݽṹ�������p5106
        VK_KHR_format_feature_flags2  :  ��չ����������Ľӿڻ������ݽṹ�������p5108
        VK_KHR_get_memory_requirements2  :  ��չ����������Ľӿڻ������ݽṹ�������p5111
        VK_KHR_get_physical_device_properties2  :  ��չ����������Ľӿڻ������ݽṹ�������p5112
        VK_KHR_image_format_list  :  ��չ����������Ľӿڻ������ݽṹ�������p5116
        VK_KHR_imageless_framebuffer  :  ��չ����������Ľӿڻ������ݽṹ�������p5117
        VK_KHR_maintenance1  :  ��չ����������Ľӿڻ������ݽṹ�������p5119
        VK_KHR_maintenance2  :  ��չ����������Ľӿڻ������ݽṹ�������p5122
        VK_KHR_maintenance3  :  ��չ����������Ľӿڻ������ݽṹ�������p5125
        VK_KHR_maintenance4  :  ��չ����������Ľӿڻ������ݽṹ�������p5127
        VK_KHR_multiview  :  ��չ����������Ľӿڻ������ݽṹ�������p5130
        VK_KHR_relaxed_block_layout  :  ��չ����������Ľӿڻ������ݽṹ�������p5132
        VK_KHR_sampler_mirror_clamp_to_edge  :  ��չ����������Ľӿڻ������ݽṹ�������p5133
        VK_KHR_sampler_ycbcr_conversion  :  ��չ����������Ľӿڻ������ݽṹ�������p5135
        VK_KHR_separate_depth_stencil_layouts  :  ��չ����������Ľӿڻ������ݽṹ�������p5141
        VK_KHR_shader_atomic_int64  :  ��չ����������Ľӿڻ������ݽṹ�������p5142
        VK_KHR_shader_draw_parameters  :  ��չ����������Ľӿڻ������ݽṹ�������p5144
        VK_KHR_shader_float16_int8  :  ��չ����������Ľӿڻ������ݽṹ�������p5146
        VK_KHR_shader_float_controls  :  ��չ����������Ľӿڻ������ݽṹ�������p5148
        VK_KHR_shader_integer_dot_product  :  ��չ����������Ľӿڻ������ݽṹ�������p5151
        VK_KHR_shader_non_semantic_info  :  ��չ����������Ľӿڻ������ݽṹ�������p5154
        VK_KHR_shader_subgroup_extended_types  :  ��չ����������Ľӿڻ������ݽṹ�������p5155
        VK_KHR_shader_terminate_invocation  :  ��չ����������Ľӿڻ������ݽṹ�������p5156
        VK_KHR_spirv_1_4  :  ��չ����������Ľӿڻ������ݽṹ�������p5158
        VK_KHR_storage_buffer_storage_class  :  ��չ����������Ľӿڻ������ݽṹ�������p5161
        VK_KHR_synchronization2  :  ��չ����������Ľӿڻ������ݽṹ�������p5162
        VK_KHR_timeline_semaphore  :  ��չ����������Ľӿڻ������ݽṹ�������p5168
        VK_KHR_uniform_buffer_standard_layout  :  ��չ����������Ľӿڻ������ݽṹ�������p5173
        VK_KHR_variable_pointers  :  ��չ����������Ľӿڻ������ݽṹ�������p5174
        VK_KHR_vulkan_memory_model  :  ��չ����������Ľӿڻ������ݽṹ�������p5177
        VK_KHR_zero_initialize_workgroup_memory  :  ��չ����������Ľӿڻ������ݽṹ�������p5179
        VK_EXT_4444_formats  :  ��չ����������Ľӿڻ������ݽṹ�������p5180
        VK_EXT_buffer_device_address  :  ��չ����������Ľӿڻ������ݽṹ�������p5182
        VK_EXT_calibrated_timestamps  :  ��չ����������Ľӿڻ������ݽṹ�������p5184
        VK_EXT_debug_marker  :  ��չ����������Ľӿڻ������ݽṹ�������p5186
        VK_EXT_debug_report  :  ��չ����������Ľӿڻ������ݽṹ�������p5191
        VK_EXT_descriptor_indexing  :  ��չ����������Ľӿڻ������ݽṹ�������p5196
        VK_EXT_extended_dynamic_state  :  ��չ����������Ľӿڻ������ݽṹ�������p5199
        VK_EXT_extended_dynamic_state2  :  ��չ����������Ľӿڻ������ݽṹ�������p5202
        VK_EXT_global_priority  :  ��չ����������Ľӿڻ������ݽṹ�������p5204
        VK_EXT_global_priority_query  :  ��չ����������Ľӿڻ������ݽṹ�������p5205
        VK_EXT_host_query_reset  :  ��չ����������Ľӿڻ������ݽṹ�������p5207
        VK_EXT_image_robustness  :  ��չ����������Ľӿڻ������ݽṹ�������p5209
        VK_EXT_index_type_uint8  :  ��չ����������Ľӿڻ������ݽṹ�������p5211
        VK_EXT_inline_uniform_block  :  ��չ����������Ľӿڻ������ݽṹ�������p5212
        VK_EXT_line_rasterization  :  ��չ����������Ľӿڻ������ݽṹ�������p5215
        VK_EXT_load_store_op_none  :  ��չ����������Ľӿڻ������ݽṹ�������p5217
        VK_EXT_pipeline_creation_cache_control  :  ��չ����������Ľӿڻ������ݽṹ�������p5219
        VK_EXT_pipeline_creation_feedback  :  ��չ����������Ľӿڻ������ݽṹ�������p5222
        VK_EXT_private_data  :  ��չ����������Ľӿڻ������ݽṹ�������p5224
        VK_EXT_sampler_filter_minmax  :  ��չ����������Ľӿڻ������ݽṹ�������p5226
        VK_EXT_scalar_block_layout  :  ��չ����������Ľӿڻ������ݽṹ�������p5228
        VK_EXT_separate_stencil_usage  :  ��չ����������Ľӿڻ������ݽṹ�������p5229
        VK_EXT_shader_demote_to_helper_invocation  :  ��չ����������Ľӿڻ������ݽṹ�������p5231
        VK_EXT_shader_subgroup_ballot  :  ��չ����������Ľӿڻ������ݽṹ�������p5232
        VK_EXT_shader_subgroup_vote  :  ��չ����������Ľӿڻ������ݽṹ�������p5235
        VK_EXT_shader_viewport_index_layer  :  ��չ����������Ľӿڻ������ݽṹ�������p5238
        VK_EXT_subgroup_size_control  :  ��չ����������Ľӿڻ������ݽṹ�������p5240
        VK_EXT_texel_buffer_alignment  :  ��չ����������Ľӿڻ������ݽṹ�������p5242
        VK_EXT_texture_compression_astc_hdr  :  ��չ����������Ľӿڻ������ݽṹ�������p5244
        VK_EXT_tooling_info  :  ��չ����������Ľӿڻ������ݽṹ�������p5246
        VK_EXT_validation_features  :  ��չ����������Ľӿڻ������ݽṹ�������p5249
        VK_EXT_validation_flags  :  ��չ����������Ľӿڻ������ݽṹ�������p5251
        VK_EXT_vertex_attribute_divisor  :  ��չ����������Ľӿڻ������ݽṹ�������p5252
        VK_EXT_ycbcr_2plane_444_formats  :  ��չ����������Ľӿڻ������ݽṹ�������p5255
        VK_AMD_draw_indirect_count  :  ��չ����������Ľӿڻ������ݽṹ�������p5257
        VK_AMD_gpu_shader_half_float  :  ��չ����������Ľӿڻ������ݽṹ�������p5258
        VK_AMD_gpu_shader_int16  :  ��չ����������Ľӿڻ������ݽṹ�������p5260
        VK_AMD_negative_viewport_height  :  ��չ����������Ľӿڻ������ݽṹ�������p5261
        VK_ARM_rasterization_order_attachment_access  :  ��չ����������Ľӿڻ������ݽṹ�������p5263
        VK_IMG_format_pvrtc  :  ��չ����������Ľӿڻ������ݽṹ�������p5265
        VK_MVK_ios_surface  :  ��չ����������Ľӿڻ������ݽṹ�������p5266
        VK_MVK_macos_surface  :  ��չ����������Ľӿڻ������ݽṹ�������p5268
        VK_NV_dedicated_allocation  :  ��չ����������Ľӿڻ������ݽṹ�������p5269
        VK_NV_external_memory  :  ��չ����������Ľӿڻ������ݽṹ�������p5272
        VK_NV_external_memory_capabilities  :  ��չ����������Ľӿڻ������ݽṹ�������p5274
        VK_NV_external_memory_win32  :  ��չ����������Ľӿڻ������ݽṹ�������p5277
        VK_NV_fragment_shader_barycentric  :  ��չ����������Ľӿڻ������ݽṹ�������p5281
        VK_NV_glsl_shader  :  ��չ����������Ľӿڻ������ݽṹ�������p5284
        VK_NV_win32_keyed_mutex  :  ��չ����������Ľӿڻ������ݽṹ�������p5286
        VK_VALVE_mutable_descriptor_type  :  ��չ����������Ľӿڻ������ݽṹ�������p5290
        
        */
    }
}

void Appendix_A_2_J_Test::Appendix_F_Test()//Vulkan Roadmap Milestones
{
    //Vulkan Roadmap Milestones  ��Roadmap milestones��ÿ��milestone ����ʾһ�������и߶����ܻ���ƽ����ն�֧�ֵ� extensions, features, limits, �Լ� formats  ���μ�p5293  ������:

    //Roadmap 2022   ������milestone��صİ汾���������ԣ�limits��������չ����Ϣ��  �μ�p5293

    //Roadmap 2024   ������milestone��صİ汾���������ԣ�limits��������չ����Ϣ��  �μ�p5297
}

void Appendix_A_2_J_Test::Appendix_G_Test()//API Boilerplate
{
	//API Boilerplate   ������һ������Vulkan API����Ļ�������,  �μ�p5300  ������:

    //Vulkan Header Files   vulkan��ͷ�ļ� �� �μ�p5300
    {
		//Vulkan Combined API Header vulkan.h (Informative) �μ�p5300

        //Vulkan Platform-Specific Header vk_platform.h (Informative)  �μ�p5300

        //Vulkan Core API Header vulkan_core.h   �μ�p5301
    }


    //Window System-Specific Header Control (Informative)   ������ƽ̨��ص���չ���� VK_KHR_win32_surface ��ͷ�ļ����μ�p5304

	//Provisional Extension Header Control (Informative)   ������ʱ�Ե���չ��ͷ�ļ����μ�p5306

	//Video Std Headers   ������Ƶ���������ص�ͷ�ļ����μ�p5307
}

void Appendix_A_2_J_Test::Appendix_H_Test()//Invariance
{
	//Invariance  ����ͬһ�汾��Vulkan API��һ���Ե������Լ������  �μ�p5308  ������:

	//Repeatability   �μ�p5308

	//Multi-pass Algorithms  �μ�p5308

    //Invariance Rules   �μ�p5308

	//Tessellation Invariance  �μ�p5310
}

void Appendix_A_2_J_Test::Appendix_I_Test()//Lexicon
{
	//Lexicon  �������ĵ� vulkan specification ʹ�õ������д�Լ��ӿ�ǰ׺��  �μ�p5311  ������:

	//Glossary  �μ�p5312  ���������ĵ� vulkan specification ʹ�õ�����ʻ�

	//Common Abbreviations  �μ�p5341  ���������ĵ� vulkan specification ʹ�õ���д�ʻ�

	//Video-Specific Abbreviations   �μ�p5342  ��������Ƶ���������ص���д�ʻ�

	//Prefixes  �μ�p5343  ������vulkan������߽ӿڵȵ�����ǰ׺
}

void Appendix_A_2_J_Test::Appendix_J_Test()//Credits (Informative)
{
    //Credits (Informative)  ����vulkan 1.3�Ĺ������Լ���ѯ�� ������:
    
	//Working Group Contributors to Vulkan  �μ�p5345  ������vulkan 1.3�Ĺ�����

    //Other Credits   �μ�p5353  ������vulkan 1.3����ѯ��


}

NS_TEST_END