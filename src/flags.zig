const std = @import("std");
const trans = @import("flags/trans.zon");
const lesbian = @import("flags/lesbian.zon");

const c = @import("flags.h");

pub export fn get_flag(name: u8) c.FLAG {
    var array: [5]u32 = [5]u32{ 0, 0, 0, 0, 0 };

    switch (name) {
        't' => array = trans.colours,
        'l' => array = lesbian.colours,
        else => array = [5]u32{ 0, 0, 0, 0, 0 },
    }

    const new_flag = c.FLAG{ .colours = array, .len = 5 };
    return new_flag;
}

