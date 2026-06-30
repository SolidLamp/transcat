const std = @import("std");
const trans = @import("flags/trans.zon");

const c = @import("flags.h");

pub export fn get_flag(name: [*:0]const u8, len: usize) c.FLAG {
    const slice = name[0..(len - 1)];
    var array: [5]u32 = [5]u32{ 0, 0, 0, 0, 0 };

    // We cannot use switch here because it is a string.
    if (std.mem.eql(u8, slice, "trans") == true) {
        array = trans.colours;
    } else {
        array = [5]u32{ 0, 0, 0, 0, 0 };
    }
    const new_flag = c.FLAG{ .colours = array, .len = 5 };
    return new_flag;
}
