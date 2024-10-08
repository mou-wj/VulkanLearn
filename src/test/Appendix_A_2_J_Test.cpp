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
	//vulkan中关于shaders的详细定义见 Khronos SPIR-V Specification 以及 Khronos SPIR-V Extended Instructions for GLSL Specification，这些见官网上https://registry.khronos.org/spir-v/


	//Versions and Formats  见p4228  ，描述SPIR-V的支持版本和格式


	//Capabilities  见p4228
	{
		/*
		描述一组支持的SPIR - V capabilities，如RayTracingNV等，见p4228
		
		这些列举在表中，见
		Table 96. List of SPIR-V Capabilities and corresponding Vulkan features, extensions, or core version  p4228



		*/

	}

	//SPIR-V Extensions  见p4238
	{
		/*
		描述一组支持的SPIR - V extensions，如SPV_KHR_variable_pointers等，见p4238

		这些列举在表中，见
		Table 97. List of SPIR-V Extensions and corresponding Vulkan extensions or core version   p4238



		*/

	}


	//Validation Rules Within a Module  参见p4243
	{
		//描述了创建SPIR-V模块需要满足的规则如下：

		//Standalone SPIR-V Validation  参见p4243 - p4253

		//Runtime SPIR-V Validation  参见p4254 - p4273

	}

	//Precision and Operation of SPIR-V Instructions  参见p4274   ， 描述了SPIR-V指令的精度和操作

	//Signedness of SPIR-V Image Accesses  参见p4279  ，描述了SPIR-V图像访问的符号性

	//Image Format and Type Matching  参见p4280  ，描述了访问图像过程中的图像格式和类型匹配

	//Compatibility Between SPIR-V Image Formats and Vulkan Formats  参见p4282  ，描述了SPIR-V图像格式和Vulkan图像格式的兼容性，见Table 100. SPIR-V and Vulkan Image Format Compatibility

	//Ray Query Precision and Operation  参见p4283 ，

}

void Appendix_A_2_J_Test::Appendix_B_Test()//Memory Model
{
	//Memory Model 描述了所有实现提供的同步机制，主要内容有:


	//Agent   参见p4285

	//Memory Location  参见p4285

	//Allocation  参见p4285


	//Memory Operation  参见p4286

	//Reference  参见p4286

	//Program-Order  参见p4286

	//Shader Call Related  参见p4287

	//Shader Call Order  参见p4287

	//Scope  参见p4287

	//Atomic Operation  参见p4288

	//Scoped Modification Order   参见p4288

	//Memory Semantics  参见p4289

	//Release Sequence  参见p4290

	//Synchronizes-With  参见p4291

	//System-Synchronizes-With  参见p4293

	//Private vs. Non-Private  参见p4293

	//Inter-Thread-Happens-Before  参见p4294

	//Happens-Before  参见p4294

	//Availability and Visibility  参见p4295

	//Availability, Visibility, and Domain Operations  参见p4296

	//Availability and Visibility Semantics  参见p4297

	//Per-Instruction Availability and Visibility Semantics  参见p4298

	//Location-Ordered  参见p4299

	//Data Race  参见p4299

	//Visible-To  参见p4300

	//Acyclicity  参见p4300

	//Shader I/O  参见p4301

	//Deallocation  参见p4301

	//Descriptions (Informative)  参见p4302 

	//Tessellation Output Ordering  参见p4302

	//Cooperative Matrix Memory Access   参见p4302

}

void Appendix_A_2_J_Test::Appendix_C_Test()//Compressed Image Formats
{
	//Compressed Image Formats 描述了Vulkan支持的压缩图像格式，主要内容有：

	//Block-Compressed Image Formats  参见p4303  ，描述含"BC"的VkFormat， 其他描述见表Table 101. Mapping of Vulkan BC formats to descriptions

	//ETC Compressed Image Formats  参见p4306  ，描述含"ETC2"以及"EAC"的VkFormat， 其他描述见表Table 102. Mapping of Vulkan ETC formats to descriptions

	//ASTC Compressed Image Formats  参见p4307  ，描述含"ASTC"的VkFormat， 其他描述见表Table 103. Mapping of Vulkan ASTC formats to descriptions

	//PVRTC Compressed Image Formats  参见p4310  ，描述含"PVRTC"的VkFormat， 其他描述见表Table 104. Mapping of Vulkan PVRTC formats to descriptions
}

void Appendix_A_2_J_Test::Appendix_D_Test()//Core Revisions (Informative)
{
	//Core Revisions (Informative) 描述了Vulkan API版本的更新信息，主要内容有：

	//Version 1.3  参见p4311 - p4320  ，描述了Vulkan 1.3版本的更新内容

	//Version 1.2  参见p4320 - p4328  ，描述了Vulkan 1.2版本的更新内容

	//Version 1.1  参见p4328 - p4340  ，描述了Vulkan 1.1版本的更新内容

	//Version 1.0  参见p4340 - p4353  ，描述了Vulkan 1.0版本的发布内容
}

void Appendix_A_2_J_Test::Appendix_E_Test()//Layers & Extensions (Informative)
{
	//Layers & Extensions (Informative) 描述了一组vulkan extensions的相关信息， 其他的注册的vulkan extensions可以见https://registry.khronos.org/vulkan/，extensions由Khronos发布的其名字带KHR，由其他厂商发布的带EXT。主要内容有：

	//Extension Dependencies  参见p4354  ，描述了Vulkan扩展开启需要特定的版本或者其他拓展支持

	//Extension Interactions  参见p4355  ，描述了一些Vulkan扩展定义的接口需要依赖其他的扩展

	//List of Current Extensions  参见p4355  ，列举当前的Vulkan扩展,基于版本1.3.285
	{
		/*
        拓展:
        VK_KHR_acceleration_structure  :  拓展描述，定义的接口或者数据结构等详情见p4363
        VK_KHR_android_surface  :  拓展描述，定义的接口或者数据结构等详情见p4378
        VK_KHR_calibrated_timestamps  :  拓展描述，定义的接口或者数据结构等详情见p4380
        VK_KHR_cooperative_matrix  :  拓展描述，定义的接口或者数据结构等详情见p4382
        VK_KHR_deferred_host_operations  :  拓展描述，定义的接口或者数据结构等详情见p4384
        VK_KHR_display  :  拓展描述，定义的接口或者数据结构等详情见p4389
        VK_KHR_display_swapchain  :  拓展描述，定义的接口或者数据结构等详情见p4396
        VK_KHR_dynamic_rendering_local_read  :  拓展描述，定义的接口或者数据结构等详情见p4399
        VK_KHR_external_fence_fd  :  拓展描述，定义的接口或者数据结构等详情见p4401
        VK_KHR_external_fence_win32  :  拓展描述，定义的接口或者数据结构等详情见p4403
        VK_KHR_external_memory_fd  :  拓展描述，定义的接口或者数据结构等详情见p4405
        VK_KHR_external_memory_win32  :  拓展描述，定义的接口或者数据结构等详情见p4407
        VK_KHR_external_semaphore_fd  :  拓展描述，定义的接口或者数据结构等详情见p4409
        VK_KHR_external_semaphore_win32  :  拓展描述，定义的接口或者数据结构等详情见p4411
        VK_KHR_fragment_shader_barycentric  :  拓展描述，定义的接口或者数据结构等详情见p4413
        VK_KHR_fragment_shading_rate  :  拓展描述，定义的接口或者数据结构等详情见p4416
        VK_KHR_get_display_properties2  :  拓展描述，定义的接口或者数据结构等详情见p4419
        VK_KHR_get_surface_capabilities2  :  拓展描述，定义的接口或者数据结构等详情见p4421
        VK_KHR_global_priority  :  拓展描述，定义的接口或者数据结构等详情见p4423
        VK_KHR_incremental_present  :  拓展描述，定义的接口或者数据结构等详情见p4425
        VK_KHR_index_type_uint8  :  拓展描述，定义的接口或者数据结构等详情见p4428
        VK_KHR_line_rasterization  :  拓展描述，定义的接口或者数据结构等详情见p4429
        VK_KHR_load_store_op_none  :  拓展描述，定义的接口或者数据结构等详情见p4431
        VK_KHR_maintenance5  :  拓展描述，定义的接口或者数据结构等详情见p4432
        VK_KHR_maintenance6  :  拓展描述，定义的接口或者数据结构等详情见p4439
        VK_KHR_map_memory2  :  拓展描述，定义的接口或者数据结构等详情见p4442
        VK_KHR_performance_query  :  拓展描述，定义的接口或者数据结构等详情见p4444
        VK_KHR_pipeline_executable_properties  :  拓展描述，定义的接口或者数据结构等详情见p4452
        VK_KHR_pipeline_library  :  拓展描述，定义的接口或者数据结构等详情见p4454
        VK_KHR_portability_enumeration  :  拓展描述，定义的接口或者数据结构等详情见p4456
        VK_KHR_present_id  :  拓展描述，定义的接口或者数据结构等详情见p4457
        VK_KHR_present_wait  :  拓展描述，定义的接口或者数据结构等详情见p4458
        VK_KHR_push_descriptor  :  拓展描述，定义的接口或者数据结构等详情见p4461
        VK_KHR_ray_query  :  拓展描述，定义的接口或者数据结构等详情见p4463
        VK_KHR_ray_tracing_maintenance1  :  拓展描述，定义的接口或者数据结构等详情见p4466
        VK_KHR_ray_tracing_pipeline  :  拓展描述，定义的接口或者数据结构等详情见p4469
        VK_KHR_ray_tracing_position_fetch  :  拓展描述，定义的接口或者数据结构等详情见p4479
        VK_KHR_shader_clock  :  拓展描述，定义的接口或者数据结构等详情见p4481
        VK_KHR_shader_expect_assume  :  拓展描述，定义的接口或者数据结构等详情见p4482
        VK_KHR_shader_float_controls2  :  拓展描述，定义的接口或者数据结构等详情见p4484
        VK_KHR_shader_maximal_reconvergence  :  拓展描述，定义的接口或者数据结构等详情见p4485
        VK_KHR_shader_quad_control  :  拓展描述，定义的接口或者数据结构等详情见p4487
        VK_KHR_shader_subgroup_rotate  :  拓展描述，定义的接口或者数据结构等详情见p4489
        VK_KHR_shader_subgroup_uniform_control_flow  :  拓展描述，定义的接口或者数据结构等详情见p4490
        VK_KHR_shared_presentable_image  :  拓展描述，定义的接口或者数据结构等详情见p4492
        VK_KHR_surface  :  拓展描述，定义的接口或者数据结构等详情见p4495
        VK_KHR_surface_protected_capabilities  :  拓展描述，定义的接口或者数据结构等详情见p4500
        VK_KHR_swapchain  :  拓展描述，定义的接口或者数据结构等详情见p4502
        VK_KHR_swapchain_mutable_format  :  拓展描述，定义的接口或者数据结构等详情见p4517
        VK_KHR_vertex_attribute_divisor  :  拓展描述，定义的接口或者数据结构等详情见p4519
        VK_KHR_video_decode_av1  :  拓展描述，定义的接口或者数据结构等详情见p4521
        VK_KHR_video_decode_h264  :  拓展描述，定义的接口或者数据结构等详情见p4523
        VK_KHR_video_decode_h265  :  拓展描述，定义的接口或者数据结构等详情见p4526
        VK_KHR_video_decode_queue  :  拓展描述，定义的接口或者数据结构等详情见p4529
        VK_KHR_video_encode_h264  :  拓展描述，定义的接口或者数据结构等详情见p4532
        VK_KHR_video_encode_h265  :  拓展描述，定义的接口或者数据结构等详情见p4538
        VK_KHR_video_encode_queue  :  拓展描述，定义的接口或者数据结构等详情见p4544
        VK_KHR_video_maintenance1  :  拓展描述，定义的接口或者数据结构等详情见p4550
        VK_KHR_video_queue  :  拓展描述，定义的接口或者数据结构等详情见p4522
        VK_KHR_wayland_surface  :  拓展描述，定义的接口或者数据结构等详情见p4558
        VK_KHR_win32_keyed_mutex  :  拓展描述，定义的接口或者数据结构等详情见p4561
        VK_KHR_win32_surface  :  拓展描述，定义的接口或者数据结构等详情见p4562
        VK_KHR_workgroup_memory_explicit_layout  :  拓展描述，定义的接口或者数据结构等详情见p4565
        VK_KHR_xcb_surface  :  拓展描述，定义的接口或者数据结构等详情见p4566
        VK_KHR_xlib_surface  :  拓展描述，定义的接口或者数据结构等详情见p4569
        VK_EXT_acquire_drm_display  :  拓展描述，定义的接口或者数据结构等详情见p4571
        VK_EXT_acquire_xlib_display  :  拓展描述，定义的接口或者数据结构等详情见p4573
        VK_EXT_astc_decode_mode  :  拓展描述，定义的接口或者数据结构等详情见p4574
        VK_EXT_attachment_feedback_loop_dynamic_state  :  拓展描述，定义的接口或者数据结构等详情见p4577
        VK_EXT_attachment_feedback_loop_layout  :  拓展描述，定义的接口或者数据结构等详情见p4578
        VK_EXT_blend_operation_advanced  :  拓展描述，定义的接口或者数据结构等详情见p4580
        VK_EXT_border_color_swizzle  :  拓展描述，定义的接口或者数据结构等详情见p4584
        VK_EXT_color_write_enable  :  拓展描述，定义的接口或者数据结构等详情见p4586
        VK_EXT_conditional_rendering  :  拓展描述，定义的接口或者数据结构等详情见p4588
        VK_EXT_conservative_rasterization  :  拓展描述，定义的接口或者数据结构等详情见p4590
        VK_EXT_custom_border_color  :  拓展描述，定义的接口或者数据结构等详情见p4592
        VK_EXT_debug_utils  :  拓展描述，定义的接口或者数据结构等详情见p4596
        VK_EXT_depth_bias_control  :  拓展描述，定义的接口或者数据结构等详情见p4605
        VK_EXT_depth_clamp_zero_one  :  拓展描述，定义的接口或者数据结构等详情见p4607
        VK_EXT_depth_clip_control  :  拓展描述，定义的接口或者数据结构等详情见p4608
        VK_EXT_depth_clip_enable  :  拓展描述，定义的接口或者数据结构等详情见p4640
        VK_EXT_depth_range_unrestricted  :  拓展描述，定义的接口或者数据结构等详情见p4611
        VK_EXT_descriptor_buffer  :  拓展描述，定义的接口或者数据结构等详情见p4613
        VK_EXT_device_address_binding_report  :  拓展描述，定义的接口或者数据结构等详情见p4617
        VK_EXT_device_fault  :  拓展描述，定义的接口或者数据结构等详情见p4620
        VK_EXT_device_memory_report  :  拓展描述，定义的接口或者数据结构等详情见p4622
        VK_EXT_direct_mode_display  :  拓展描述，定义的接口或者数据结构等详情见p4626
        VK_EXT_directfb_surface  :  拓展描述，定义的接口或者数据结构等详情见p4628
        VK_EXT_discard_rectangles  :  拓展描述，定义的接口或者数据结构等详情见p4629
        VK_EXT_display_control  :  拓展描述，定义的接口或者数据结构等详情见p4631
        VK_EXT_display_surface_counter  :  拓展描述，定义的接口或者数据结构等详情见p4633
        VK_EXT_dynamic_rendering_unused_attachments  :  拓展描述，定义的接口或者数据结构等详情见p4635
        VK_EXT_extended_dynamic_state3  :  拓展描述，定义的接口或者数据结构等详情见p4636
        VK_EXT_external_memory_acquire_unmodified  :  拓展描述，定义的接口或者数据结构等详情见p4643
        VK_EXT_external_memory_dma_buf  :  拓展描述，定义的接口或者数据结构等详情见p4644
        VK_EXT_external_memory_host  :  拓展描述，定义的接口或者数据结构等详情见p4646
        VK_EXT_filter_cubic  :  拓展描述，定义的接口或者数据结构等详情见p4648
        VK_EXT_fragment_density_map  :  拓展描述，定义的接口或者数据结构等详情见p4650
        VK_EXT_fragment_density_map2  :  拓展描述，定义的接口或者数据结构等详情见p4653
        VK_EXT_fragment_shader_interlock  :  拓展描述，定义的接口或者数据结构等详情见p4654
        VK_EXT_frame_boundary  :  拓展描述，定义的接口或者数据结构等详情见p4656
        VK_EXT_full_screen_exclusive  :  拓展描述，定义的接口或者数据结构等详情见p4658
        VK_EXT_graphics_pipeline_library  :  拓展描述，定义的接口或者数据结构等详情见p4662
        VK_EXT_hdr_metadata  :  拓展描述，定义的接口或者数据结构等详情见p4664
        VK_EXT_headless_surface  :  拓展描述，定义的接口或者数据结构等详情见p4666
        VK_EXT_host_image_copy  :  拓展描述，定义的接口或者数据结构等详情见p4667
        VK_EXT_image_2d_view_of_3d  :  拓展描述，定义的接口或者数据结构等详情见p4671
        VK_EXT_image_compression_control  :  拓展描述，定义的接口或者数据结构等详情见p4672
        VK_EXT_image_compression_control_swapchain  :  拓展描述，定义的接口或者数据结构等详情见p4675
        VK_EXT_image_drm_format_modifier  :  拓展描述，定义的接口或者数据结构等详情见p4676
        VK_EXT_image_sliced_view_of_3d  :  拓展描述，定义的接口或者数据结构等详情见p4684
        VK_EXT_image_view_min_lod  :  拓展描述，定义的接口或者数据结构等详情见p4685
        VK_EXT_layer_settings  :  拓展描述，定义的接口或者数据结构等详情见p4687
        VK_EXT_legacy_dithering  :  拓展描述，定义的接口或者数据结构等详情见p4690
        VK_EXT_legacy_vertex_attributes  :  拓展描述，定义的接口或者数据结构等详情见p4692
        VK_EXT_map_memory_placed  :  拓展描述，定义的接口或者数据结构等详情见p4694
        VK_EXT_memory_budget  :  拓展描述，定义的接口或者数据结构等详情见p4695
        VK_EXT_memory_priority  :  拓展描述，定义的接口或者数据结构等详情见p4697
        VK_EXT_mesh_shader  :  拓展描述，定义的接口或者数据结构等详情见p4698
        VK_EXT_metal_objects  :  拓展描述，定义的接口或者数据结构等详情见p4702
        VK_EXT_metal_surface  :  拓展描述，定义的接口或者数据结构等详情见p4705
        VK_EXT_multi_draw  :  拓展描述，定义的接口或者数据结构等详情见p4706
        VK_EXT_multisampled_render_to_single_sampled  :  拓展描述，定义的接口或者数据结构等详情见p4708
        VK_EXT_mutable_descriptor_type  :  拓展描述，定义的接口或者数据结构等详情见p4710
        VK_EXT_nested_command_buffer  :  拓展描述，定义的接口或者数据结构等详情见p4712
        VK_EXT_non_seamless_cube_map  :  拓展描述，定义的接口或者数据结构等详情见p4714
        VK_EXT_opacity_micromap  :  拓展描述，定义的接口或者数据结构等详情见p4716
        VK_EXT_pageable_device_local_memory  :  拓展描述，定义的接口或者数据结构等详情见p4721
        VK_EXT_pci_bus_info  :  拓展描述，定义的接口或者数据结构等详情见p4723
        VK_EXT_physical_device_drm  :  拓展描述，定义的接口或者数据结构等详情见p4725
        VK_EXT_pipeline_library_group_handles  :  拓展描述，定义的接口或者数据结构等详情见p4726
        VK_EXT_pipeline_properties  :  拓展描述，定义的接口或者数据结构等详情见p4728
        VK_EXT_pipeline_protected_access  :  拓展描述，定义的接口或者数据结构等详情见p4730
        VK_EXT_pipeline_robustness  :  拓展描述，定义的接口或者数据结构等详情见p4732
        VK_EXT_post_depth_coverage  :  拓展描述，定义的接口或者数据结构等详情见p4734
        VK_EXT_primitive_topology_list_restart  :  拓展描述，定义的接口或者数据结构等详情见p4735
        VK_EXT_primitives_generated_query  :  拓展描述，定义的接口或者数据结构等详情见p4737
        VK_EXT_provoking_vertex  :  拓展描述，定义的接口或者数据结构等详情见p4739
        VK_EXT_queue_family_foreign  :  拓展描述，定义的接口或者数据结构等详情见p4741
        VK_EXT_rasterization_order_attachment_access  :  拓展描述，定义的接口或者数据结构等详情见p4743
        VK_EXT_rgba10x6_formats  :  拓展描述，定义的接口或者数据结构等详情见p4745
        VK_EXT_robustness2  :  拓展描述，定义的接口或者数据结构等详情见p4746
        VK_EXT_sample_locations  :  拓展描述，定义的接口或者数据结构等详情见p4748
        VK_EXT_shader_atomic_float  :  拓展描述，定义的接口或者数据结构等详情见p4750
        VK_EXT_shader_atomic_float2  :  拓展描述，定义的接口或者数据结构等详情见p4752
        VK_EXT_shader_image_atomic_int64  :  拓展描述，定义的接口或者数据结构等详情见p4754
        VK_EXT_shader_module_identifier  :  拓展描述，定义的接口或者数据结构等详情见p4755
        VK_EXT_shader_object  :  拓展描述，定义的接口或者数据结构等详情见p4758
        VK_EXT_shader_stencil_export  :  拓展描述，定义的接口或者数据结构等详情见p4770
        VK_EXT_shader_tile_image  :  拓展描述，定义的接口或者数据结构等详情见p4771
        VK_EXT_subpass_merge_feedback  :  拓展描述，定义的接口或者数据结构等详情见p4774
        VK_EXT_surface_maintenance1  :  拓展描述，定义的接口或者数据结构等详情见p4775
        VK_EXT_swapchain_colorspace  :  拓展描述，定义的接口或者数据结构等详情见p4777
        VK_EXT_swapchain_maintenance1  :  拓展描述，定义的接口或者数据结构等详情见p4780
        VK_EXT_transform_feedback  :  拓展描述，定义的接口或者数据结构等详情见p4782
        VK_EXT_validation_cache  :  拓展描述，定义的接口或者数据结构等详情见p4785
        VK_EXT_vertex_input_dynamic_state  :  拓展描述，定义的接口或者数据结构等详情见p4787
        VK_EXT_ycbcr_image_arrays  :  拓展描述，定义的接口或者数据结构等详情见p4789
        VK_AMD_buffer_marker  :  拓展描述，定义的接口或者数据结构等详情见p4790
        VK_AMD_device_coherent_memory  :  拓展描述，定义的接口或者数据结构等详情见p4791
        VK_AMD_display_native_hdr  :  拓展描述，定义的接口或者数据结构等详情见p4793
        VK_AMD_gcn_shader  :  拓展描述，定义的接口或者数据结构等详情见p4795
        VK_AMD_memory_overallocation_behavior  :  拓展描述，定义的接口或者数据结构等详情见p4796
        VK_AMD_mixed_attachment_samples  :  拓展描述，定义的接口或者数据结构等详情见p4797
        VK_AMD_pipeline_compiler_control  :  拓展描述，定义的接口或者数据结构等详情见p4799
        VK_AMD_rasterization_order  :  拓展描述，定义的接口或者数据结构等详情见p4800
        VK_AMD_shader_ballot  :  拓展描述，定义的接口或者数据结构等详情见p4803
        VK_AMD_shader_core_properties  :  拓展描述，定义的接口或者数据结构等详情见p4804
        VK_AMD_shader_core_properties2  :  拓展描述，定义的接口或者数据结构等详情见p4807
        VK_AMD_shader_early_and_late_fragment_tests  :  拓展描述，定义的接口或者数据结构等详情见p4808
        VK_AMD_shader_explicit_vertex_parameter  :  拓展描述，定义的接口或者数据结构等详情见p4810
        VK_AMD_shader_fragment_mask  :  拓展描述，定义的接口或者数据结构等详情见p4811
        VK_AMD_shader_image_load_store_lod  :  拓展描述，定义的接口或者数据结构等详情见p4813
        VK_AMD_shader_info  :  拓展描述，定义的接口或者数据结构等详情见p4814
        VK_AMD_shader_trinary_minmax  :  拓展描述，定义的接口或者数据结构等详情见p4817
        VK_AMD_texture_gather_bias_lod  :  拓展描述，定义的接口或者数据结构等详情见p4818
        VK_ANDROID_external_format_resolve  :  拓展描述，定义的接口或者数据结构等详情见p4821
        VK_ANDROID_external_memory_android_hardware_buffer  :  拓展描述，定义的接口或者数据结构等详情见p4823
        VK_ARM_render_pass_striped  :  拓展描述，定义的接口或者数据结构等详情见p4827
        VK_ARM_scheduling_controls  :  拓展描述，定义的接口或者数据结构等详情见p4829
        VK_ARM_shader_core_builtins  :  拓展描述，定义的接口或者数据结构等详情见p4831
        VK_ARM_shader_core_properties  :  拓展描述，定义的接口或者数据结构等详情见p4832
        VK_FUCHSIA_buffer_collection  :  拓展描述，定义的接口或者数据结构等详情见p4834
        VK_FUCHSIA_external_memory  :  拓展描述，定义的接口或者数据结构等详情见p4837
        VK_FUCHSIA_external_semaphore  :  拓展描述，定义的接口或者数据结构等详情见p4839
        VK_FUCHSIA_imagepipe_surface  :  拓展描述，定义的接口或者数据结构等详情见p4840
        VK_GGP_frame_token  :  拓展描述，定义的接口或者数据结构等详情见p4842
        VK_GGP_stream_descriptor_surface  :  拓展描述，定义的接口或者数据结构等详情见p4843
        VK_GOOGLE_decorate_string  :  拓展描述，定义的接口或者数据结构等详情见p4845
        VK_GOOGLE_display_timing  :  拓展描述，定义的接口或者数据结构等详情见p4846
        VK_GOOGLE_hlsl_functionality1  :  拓展描述，定义的接口或者数据结构等详情见p4848
        VK_GOOGLE_surfaceless_query  :  拓展描述，定义的接口或者数据结构等详情见p4849
        VK_GOOGLE_user_type  :  拓展描述，定义的接口或者数据结构等详情见p4850
        VK_HUAWEI_cluster_culling_shader  :  拓展描述，定义的接口或者数据结构等详情见p4851
        VK_HUAWEI_invocation_mask  :  拓展描述，定义的接口或者数据结构等详情见p4857
        VK_HUAWEI_subpass_shading  :  拓展描述，定义的接口或者数据结构等详情见p4860
        VK_IMG_filter_cubic  :  拓展描述，定义的接口或者数据结构等详情见p4867
        VK_IMG_relaxed_line_rasterization  :  拓展描述，定义的接口或者数据结构等详情见p4868
        VK_INTEL_performance_query  :  拓展描述，定义的接口或者数据结构等详情见p4870
        VK_INTEL_shader_integer_functions2  :  拓展描述，定义的接口或者数据结构等详情见p4875
        VK_LUNARG_direct_driver_loading  :  拓展描述，定义的接口或者数据结构等详情见p4876
        VK_MESA_image_alignment_control  :  拓展描述，定义的接口或者数据结构等详情见p4878
        VK_MSFT_layered_driver  :  拓展描述，定义的接口或者数据结构等详情见p4880
        VK_NN_vi_surface  :  拓展描述，定义的接口或者数据结构等详情见p4881
        VK_NV_acquire_winrt_display  :  拓展描述，定义的接口或者数据结构等详情见p4883
        VK_NV_clip_space_w_scaling  :  拓展描述，定义的接口或者数据结构等详情见p4885
        VK_NV_compute_shader_derivatives  :  拓展描述，定义的接口或者数据结构等详情见p4889
        VK_NV_cooperative_matrix  :  拓展描述，定义的接口或者数据结构等详情见p4891
        VK_NV_copy_memory_indirect  :  拓展描述，定义的接口或者数据结构等详情见p4893
        VK_NV_corner_sampled_image  :  拓展描述，定义的接口或者数据结构等详情见p4895
        VK_NV_coverage_reduction_mode  :  拓展描述，定义的接口或者数据结构等详情见p4897
        VK_NV_dedicated_allocation_image_aliasing  :  拓展描述，定义的接口或者数据结构等详情见p4899
        VK_NV_descriptor_pool_overallocation  :  拓展描述，定义的接口或者数据结构等详情见p4901
        VK_NV_device_diagnostic_checkpoints  :  拓展描述，定义的接口或者数据结构等详情见p4902
        VK_NV_device_diagnostics_config  :  拓展描述，定义的接口或者数据结构等详情见p4904
        VK_NV_device_generated_commands  :  拓展描述，定义的接口或者数据结构等详情见p4905
        VK_NV_device_generated_commands_compute  :  拓展描述，定义的接口或者数据结构等详情见p4913
        VK_NV_extended_sparse_address_space  :  拓展描述，定义的接口或者数据结构等详情见p4915
        VK_NV_external_memory_rdma  :  拓展描述，定义的接口或者数据结构等详情见p4916
        VK_NV_fill_rectangle  :  拓展描述，定义的接口或者数据结构等详情见p4920
        VK_NV_fragment_coverage_to_color  :  拓展描述，定义的接口或者数据结构等详情见p4921
        VK_NV_fragment_shading_rate_enums  :  拓展描述，定义的接口或者数据结构等详情见p4922
        VK_NV_framebuffer_mixed_samples  :  拓展描述，定义的接口或者数据结构等详情见p4925
        VK_NV_geometry_shader_passthrough  :  拓展描述，定义的接口或者数据结构等详情见p4927
        VK_NV_inherited_viewport_scissor  :  拓展描述，定义的接口或者数据结构等详情见p4930
        VK_NV_linear_color_attachment  :  拓展描述，定义的接口或者数据结构等详情见p4932
        VK_NV_low_latency  :  拓展描述，定义的接口或者数据结构等详情见p4934
        VK_NV_low_latency2  :  拓展描述，定义的接口或者数据结构等详情见p4934
        VK_NV_memory_decompression  :  拓展描述，定义的接口或者数据结构等详情见p4937
        VK_NV_mesh_shader  :  拓展描述，定义的接口或者数据结构等详情见p4939
        VK_NV_optical_flow  :  拓展描述，定义的接口或者数据结构等详情见p4943
        VK_NV_per_stage_descriptor_set  :  拓展描述，定义的接口或者数据结构等详情见p4948
        VK_NV_present_barrier  :  拓展描述，定义的接口或者数据结构等详情见p4949
        VK_NV_raw_access_chains  :  拓展描述，定义的接口或者数据结构等详情见p4951
        VK_NV_ray_tracing  :  拓展描述，定义的接口或者数据结构等详情见p4952
        VK_NV_ray_tracing_invocation_reorder  :  拓展描述，定义的接口或者数据结构等详情见p4959
        VK_NV_ray_tracing_motion_blur  :  拓展描述，定义的接口或者数据结构等详情见p4963
        VK_NV_ray_tracing_validation  :  拓展描述，定义的接口或者数据结构等详情见p4966
        VK_NV_representative_fragment_test  :  拓展描述，定义的接口或者数据结构等详情见p4967
        VK_NV_sample_mask_override_coverage  :  拓展描述，定义的接口或者数据结构等详情见p4969
        VK_NV_scissor_exclusive  :  拓展描述，定义的接口或者数据结构等详情见p4971
        VK_NV_shader_atomic_float16_vector  :  拓展描述，定义的接口或者数据结构等详情见p4973
        VK_NV_shader_image_footprint  :  拓展描述，定义的接口或者数据结构等详情见p4974
        VK_NV_shader_sm_builtins  :  拓展描述，定义的接口或者数据结构等详情见p4979
        VK_NV_shader_subgroup_partitioned  :  拓展描述，定义的接口或者数据结构等详情见p4981
        VK_NV_shading_rate_image  :  拓展描述，定义的接口或者数据结构等详情见p4982
        VK_NV_viewport_array2  :  拓展描述，定义的接口或者数据结构等详情见p4986
        VK_NV_viewport_swizzle  :  拓展描述，定义的接口或者数据结构等详情见p4988
        VK_NVX_binary_import  :  拓展描述，定义的接口或者数据结构等详情见p4992
        VK_NVX_image_view_handle  :  拓展描述，定义的接口或者数据结构等详情见p5000
        VK_NVX_multiview_per_view_attributes  :  拓展描述，定义的接口或者数据结构等详情见p5001
        VK_QCOM_filter_cubic_clamp  :  拓展描述，定义的接口或者数据结构等详情见p5003
        VK_QCOM_filter_cubic_weights  :  拓展描述，定义的接口或者数据结构等详情见p5005
        VK_QCOM_fragment_density_map_offset  :  拓展描述，定义的接口或者数据结构等详情见p5007
        VK_QCOM_image_processing  :  拓展描述，定义的接口或者数据结构等详情见p5008
        VK_QCOM_image_processing2  :  拓展描述，定义的接口或者数据结构等详情见p5011
        VK_QCOM_multiview_per_view_render_areas  :  拓展描述，定义的接口或者数据结构等详情见p5014
        VK_QCOM_multiview_per_view_viewports  :  拓展描述，定义的接口或者数据结构等详情见p5016
        VK_QCOM_render_pass_shader_resolve  :  拓展描述，定义的接口或者数据结构等详情见p5018
        VK_QCOM_render_pass_store_ops  :  拓展描述，定义的接口或者数据结构等详情见p5021
        VK_QCOM_render_pass_transform  :  拓展描述，定义的接口或者数据结构等详情见p5022
        VK_QCOM_rotated_copy_commands  :  拓展描述，定义的接口或者数据结构等详情见p5026
        VK_QCOM_tile_properties  :  拓展描述，定义的接口或者数据结构等详情见p5028
        VK_QCOM_ycbcr_degamma  :  拓展描述，定义的接口或者数据结构等详情见p5030
        VK_QNX_external_memory_screen_buffer  :  拓展描述，定义的接口或者数据结构等详情见p5032
        VK_QNX_screen_surface  :  拓展描述，定义的接口或者数据结构等详情见p5034
        VK_SEC_amigo_profiling  :  拓展描述，定义的接口或者数据结构等详情见p5035
        VK_VALVE_descriptor_set_host_mapping  :  拓展描述，定义的接口或者数据结构等详情见p5038

        */
    }

    //List of Provisional Extensions  参见p5042  ，列举临时的拓展,基于版本1.3.285
    {
        /*
        拓展:
        VK_KHR_portability_subset  :  拓展描述，定义的接口或者数据结构等详情见p5053
        VK_AMDX_shader_enqueue  :  拓展描述，定义的接口或者数据结构等详情见p5045
        VK_NV_cuda_kernel_launch  :  拓展描述，定义的接口或者数据结构等详情见p5048
        VK_NV_displacement_micromap  :  拓展描述，定义的接口或者数据结构等详情见p5050
        
        */

    }

	//List of Deprecated Extensions  参见p5052  ，列举已废弃的拓展,基于版本1.3.285
    {
        /*
        拓展:
        VK_KHR_16bit_storage  :  拓展描述，定义的接口或者数据结构等详情见p5057
        VK_KHR_8bit_storage  :  拓展描述，定义的接口或者数据结构等详情见p5058
        VK_KHR_bind_memory2  :  拓展描述，定义的接口或者数据结构等详情见p5059
        VK_KHR_buffer_device_address  :  拓展描述，定义的接口或者数据结构等详情见p5061
        VK_KHR_copy_commands2  :  拓展描述，定义的接口或者数据结构等详情见p5064
        VK_KHR_create_renderpass2  :  拓展描述，定义的接口或者数据结构等详情见p5066
        VK_KHR_dedicated_allocation  :  拓展描述，定义的接口或者数据结构等详情见p5068
        VK_KHR_depth_stencil_resolve  :  拓展描述，定义的接口或者数据结构等详情见p5072
        VK_KHR_descriptor_update_template  :  拓展描述，定义的接口或者数据结构等详情见p5074
        VK_KHR_device_group  :  拓展描述，定义的接口或者数据结构等详情见p5077
        VK_KHR_device_group_creation  :  拓展描述，定义的接口或者数据结构等详情见p5082
        VK_KHR_draw_indirect_count  :  拓展描述，定义的接口或者数据结构等详情见p5084
        VK_KHR_driver_properties  :  拓展描述，定义的接口或者数据结构等详情见p5085
        VK_KHR_dynamic_rendering  :  拓展描述，定义的接口或者数据结构等详情见p5087
        VK_KHR_external_fence  :  拓展描述，定义的接口或者数据结构等详情见p5091
        VK_KHR_external_fence_capabilities  :  拓展描述，定义的接口或者数据结构等详情见p5093
        VK_KHR_external_memory  :  拓展描述，定义的接口或者数据结构等详情见p5095
        VK_KHR_external_memory_capabilities  :  拓展描述，定义的接口或者数据结构等详情见p5100
        VK_KHR_external_semaphore  :  拓展描述，定义的接口或者数据结构等详情见p5104
        VK_KHR_external_semaphore_capabilities  :  拓展描述，定义的接口或者数据结构等详情见p5106
        VK_KHR_format_feature_flags2  :  拓展描述，定义的接口或者数据结构等详情见p5108
        VK_KHR_get_memory_requirements2  :  拓展描述，定义的接口或者数据结构等详情见p5111
        VK_KHR_get_physical_device_properties2  :  拓展描述，定义的接口或者数据结构等详情见p5112
        VK_KHR_image_format_list  :  拓展描述，定义的接口或者数据结构等详情见p5116
        VK_KHR_imageless_framebuffer  :  拓展描述，定义的接口或者数据结构等详情见p5117
        VK_KHR_maintenance1  :  拓展描述，定义的接口或者数据结构等详情见p5119
        VK_KHR_maintenance2  :  拓展描述，定义的接口或者数据结构等详情见p5122
        VK_KHR_maintenance3  :  拓展描述，定义的接口或者数据结构等详情见p5125
        VK_KHR_maintenance4  :  拓展描述，定义的接口或者数据结构等详情见p5127
        VK_KHR_multiview  :  拓展描述，定义的接口或者数据结构等详情见p5130
        VK_KHR_relaxed_block_layout  :  拓展描述，定义的接口或者数据结构等详情见p5132
        VK_KHR_sampler_mirror_clamp_to_edge  :  拓展描述，定义的接口或者数据结构等详情见p5133
        VK_KHR_sampler_ycbcr_conversion  :  拓展描述，定义的接口或者数据结构等详情见p5135
        VK_KHR_separate_depth_stencil_layouts  :  拓展描述，定义的接口或者数据结构等详情见p5141
        VK_KHR_shader_atomic_int64  :  拓展描述，定义的接口或者数据结构等详情见p5142
        VK_KHR_shader_draw_parameters  :  拓展描述，定义的接口或者数据结构等详情见p5144
        VK_KHR_shader_float16_int8  :  拓展描述，定义的接口或者数据结构等详情见p5146
        VK_KHR_shader_float_controls  :  拓展描述，定义的接口或者数据结构等详情见p5148
        VK_KHR_shader_integer_dot_product  :  拓展描述，定义的接口或者数据结构等详情见p5151
        VK_KHR_shader_non_semantic_info  :  拓展描述，定义的接口或者数据结构等详情见p5154
        VK_KHR_shader_subgroup_extended_types  :  拓展描述，定义的接口或者数据结构等详情见p5155
        VK_KHR_shader_terminate_invocation  :  拓展描述，定义的接口或者数据结构等详情见p5156
        VK_KHR_spirv_1_4  :  拓展描述，定义的接口或者数据结构等详情见p5158
        VK_KHR_storage_buffer_storage_class  :  拓展描述，定义的接口或者数据结构等详情见p5161
        VK_KHR_synchronization2  :  拓展描述，定义的接口或者数据结构等详情见p5162
        VK_KHR_timeline_semaphore  :  拓展描述，定义的接口或者数据结构等详情见p5168
        VK_KHR_uniform_buffer_standard_layout  :  拓展描述，定义的接口或者数据结构等详情见p5173
        VK_KHR_variable_pointers  :  拓展描述，定义的接口或者数据结构等详情见p5174
        VK_KHR_vulkan_memory_model  :  拓展描述，定义的接口或者数据结构等详情见p5177
        VK_KHR_zero_initialize_workgroup_memory  :  拓展描述，定义的接口或者数据结构等详情见p5179
        VK_EXT_4444_formats  :  拓展描述，定义的接口或者数据结构等详情见p5180
        VK_EXT_buffer_device_address  :  拓展描述，定义的接口或者数据结构等详情见p5182
        VK_EXT_calibrated_timestamps  :  拓展描述，定义的接口或者数据结构等详情见p5184
        VK_EXT_debug_marker  :  拓展描述，定义的接口或者数据结构等详情见p5186
        VK_EXT_debug_report  :  拓展描述，定义的接口或者数据结构等详情见p5191
        VK_EXT_descriptor_indexing  :  拓展描述，定义的接口或者数据结构等详情见p5196
        VK_EXT_extended_dynamic_state  :  拓展描述，定义的接口或者数据结构等详情见p5199
        VK_EXT_extended_dynamic_state2  :  拓展描述，定义的接口或者数据结构等详情见p5202
        VK_EXT_global_priority  :  拓展描述，定义的接口或者数据结构等详情见p5204
        VK_EXT_global_priority_query  :  拓展描述，定义的接口或者数据结构等详情见p5205
        VK_EXT_host_query_reset  :  拓展描述，定义的接口或者数据结构等详情见p5207
        VK_EXT_image_robustness  :  拓展描述，定义的接口或者数据结构等详情见p5209
        VK_EXT_index_type_uint8  :  拓展描述，定义的接口或者数据结构等详情见p5211
        VK_EXT_inline_uniform_block  :  拓展描述，定义的接口或者数据结构等详情见p5212
        VK_EXT_line_rasterization  :  拓展描述，定义的接口或者数据结构等详情见p5215
        VK_EXT_load_store_op_none  :  拓展描述，定义的接口或者数据结构等详情见p5217
        VK_EXT_pipeline_creation_cache_control  :  拓展描述，定义的接口或者数据结构等详情见p5219
        VK_EXT_pipeline_creation_feedback  :  拓展描述，定义的接口或者数据结构等详情见p5222
        VK_EXT_private_data  :  拓展描述，定义的接口或者数据结构等详情见p5224
        VK_EXT_sampler_filter_minmax  :  拓展描述，定义的接口或者数据结构等详情见p5226
        VK_EXT_scalar_block_layout  :  拓展描述，定义的接口或者数据结构等详情见p5228
        VK_EXT_separate_stencil_usage  :  拓展描述，定义的接口或者数据结构等详情见p5229
        VK_EXT_shader_demote_to_helper_invocation  :  拓展描述，定义的接口或者数据结构等详情见p5231
        VK_EXT_shader_subgroup_ballot  :  拓展描述，定义的接口或者数据结构等详情见p5232
        VK_EXT_shader_subgroup_vote  :  拓展描述，定义的接口或者数据结构等详情见p5235
        VK_EXT_shader_viewport_index_layer  :  拓展描述，定义的接口或者数据结构等详情见p5238
        VK_EXT_subgroup_size_control  :  拓展描述，定义的接口或者数据结构等详情见p5240
        VK_EXT_texel_buffer_alignment  :  拓展描述，定义的接口或者数据结构等详情见p5242
        VK_EXT_texture_compression_astc_hdr  :  拓展描述，定义的接口或者数据结构等详情见p5244
        VK_EXT_tooling_info  :  拓展描述，定义的接口或者数据结构等详情见p5246
        VK_EXT_validation_features  :  拓展描述，定义的接口或者数据结构等详情见p5249
        VK_EXT_validation_flags  :  拓展描述，定义的接口或者数据结构等详情见p5251
        VK_EXT_vertex_attribute_divisor  :  拓展描述，定义的接口或者数据结构等详情见p5252
        VK_EXT_ycbcr_2plane_444_formats  :  拓展描述，定义的接口或者数据结构等详情见p5255
        VK_AMD_draw_indirect_count  :  拓展描述，定义的接口或者数据结构等详情见p5257
        VK_AMD_gpu_shader_half_float  :  拓展描述，定义的接口或者数据结构等详情见p5258
        VK_AMD_gpu_shader_int16  :  拓展描述，定义的接口或者数据结构等详情见p5260
        VK_AMD_negative_viewport_height  :  拓展描述，定义的接口或者数据结构等详情见p5261
        VK_ARM_rasterization_order_attachment_access  :  拓展描述，定义的接口或者数据结构等详情见p5263
        VK_IMG_format_pvrtc  :  拓展描述，定义的接口或者数据结构等详情见p5265
        VK_MVK_ios_surface  :  拓展描述，定义的接口或者数据结构等详情见p5266
        VK_MVK_macos_surface  :  拓展描述，定义的接口或者数据结构等详情见p5268
        VK_NV_dedicated_allocation  :  拓展描述，定义的接口或者数据结构等详情见p5269
        VK_NV_external_memory  :  拓展描述，定义的接口或者数据结构等详情见p5272
        VK_NV_external_memory_capabilities  :  拓展描述，定义的接口或者数据结构等详情见p5274
        VK_NV_external_memory_win32  :  拓展描述，定义的接口或者数据结构等详情见p5277
        VK_NV_fragment_shader_barycentric  :  拓展描述，定义的接口或者数据结构等详情见p5281
        VK_NV_glsl_shader  :  拓展描述，定义的接口或者数据结构等详情见p5284
        VK_NV_win32_keyed_mutex  :  拓展描述，定义的接口或者数据结构等详情见p5286
        VK_VALVE_mutable_descriptor_type  :  拓展描述，定义的接口或者数据结构等详情见p5290
        
        */
    }
}

void Appendix_A_2_J_Test::Appendix_F_Test()//Vulkan Roadmap Milestones
{
    //Vulkan Roadmap Milestones  对Roadmap milestones的每个milestone 都表示一组主流中高端智能机，平板等终端支持的 extensions, features, limits, 以及 formats  ，参见p5293  ，包含:

    //Roadmap 2022   描述该milestone相关的版本，所需特性，limits，所需拓展等信息，  参见p5293

    //Roadmap 2024   描述该milestone相关的版本，所需特性，limits，所需拓展等信息，  参见p5297
}

void Appendix_A_2_J_Test::Appendix_G_Test()//API Boilerplate
{
	//API Boilerplate   描述了一个完整Vulkan API所需的基本内容,  参见p5300  ，包含:

    //Vulkan Header Files   vulkan的头文件 ， 参见p5300
    {
		//Vulkan Combined API Header vulkan.h (Informative) 参见p5300

        //Vulkan Platform-Specific Header vk_platform.h (Informative)  参见p5300

        //Vulkan Core API Header vulkan_core.h   参见p5301
    }


    //Window System-Specific Header Control (Informative)   描述和平台相关的拓展，如 VK_KHR_win32_surface 的头文件，参见p5304

	//Provisional Extension Header Control (Informative)   描述临时性的拓展的头文件，参见p5306

	//Video Std Headers   描述视频编码解码相关的头文件，参见p5307
}

void Appendix_A_2_J_Test::Appendix_H_Test()//Invariance
{
	//Invariance  描述同一版本的Vulkan API的一致性的理由以及其规则，  参见p5308  ，包含:

	//Repeatability   参见p5308

	//Multi-pass Algorithms  参见p5308

    //Invariance Rules   参见p5308

	//Tessellation Invariance  参见p5310
}

void Appendix_A_2_J_Test::Appendix_I_Test()//Lexicon
{
	//Lexicon  描述该文档 vulkan specification 使用的术语，缩写以及接口前缀，  参见p5311  ，包含:

	//Glossary  参见p5312  ，描述该文档 vulkan specification 使用的术语词汇

	//Common Abbreviations  参见p5341  ，描述该文档 vulkan specification 使用的缩写词汇

	//Video-Specific Abbreviations   参见p5342  ，描述视频编码解码相关的缩写词汇

	//Prefixes  参见p5343  ，描述vulkan对象或者接口等的名字前缀
}

void Appendix_A_2_J_Test::Appendix_J_Test()//Credits (Informative)
{
    //Credits (Informative)  描述vulkan 1.3的贡献者以及咨询组 ，包含:
    
	//Working Group Contributors to Vulkan  参见p5345  ，描述vulkan 1.3的贡献者

    //Other Credits   参见p5353  ，描述vulkan 1.3的咨询组


}

NS_TEST_END