-- ======================================================================================
-- File         : global.lua
-- Author       : Wu Jie 
-- Last Change  : 10/29/2010 | 14:15:25 PM | Friday,October
-- Description  : 
-- ======================================================================================

--/////////////////////////////////////////////////////////////////////////////
--
--/////////////////////////////////////////////////////////////////////////////

module("global")

--/////////////////////////////////////////////////////////////////////////////
--
--/////////////////////////////////////////////////////////////////////////////

fps = 60.0
dt = 0.0
if fps == 60.0 then
    dt = 0.0167
elseif fps == 30.0 then
    dt = 0.0333
end
