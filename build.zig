const std = @import("std");

pub fn build(b: *std.Build) void {
    const target = b.standardTargetOptions(.{});
    const mode = b.standardOptimizeOption(.{});

    const lib_mod = b.addModule("main", .{
        .target = target,
        .optimize = mode,
        .link_libc = true,
    });

    lib_mod.addCSourceFile(.{
        .file = b.path("src/main.c"),
        .flags = &.{ "-std=gnu89", "-Wall", "-pedantic" },
    });

    const exe_mod = b.addExecutable(.{
        .name = "transcat",
        .root_module = lib_mod,
    });

    b.installArtifact(exe_mod);
}
