//! For usage with Zig 0.16.0 - remember, Zig is unstable!

const std = @import("std");

pub fn build(b: *std.Build) void {
    const target = b.standardTargetOptions(.{});
    const mode = b.standardOptimizeOption(.{});

    const flagsheader = b.addTranslateC(.{
        .root_source_file = b.path("./src/flags.h"),
        .target = target,
        .optimize = mode,
        .link_libc = true,
    });

    const libzigs = b.addLibrary(.{
        .name = "prideflaglib",
        .linkage = .static,
        .root_module = b.createModule(.{
            .root_source_file = b.path("src/flags.zig"),
            .target = target,
            .optimize = mode,
            .link_libc = true,
            .imports = &.{
                .{ .name = "flags.h", .module = flagsheader.createModule() },
            },
        }),
    });

    const lib_mod = b.addModule("main", .{
        .target = target,
        .optimize = mode,
        .link_libc = true,
    });

    lib_mod.addCSourceFile(.{
        .file = b.path("src/main.c"),
        .flags = &.{ "-std=gnu89", "-Wall", "-pedantic" },
    });

    const exe = b.addExecutable(.{
        .name = "transcat",
        .root_module = lib_mod,
    });
    exe.root_module.linkLibrary(libzigs);

    b.installArtifact(libzigs);
    b.installArtifact(exe);
}