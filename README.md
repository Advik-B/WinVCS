# WinVCS
> An NTFS-only version control system for Windows.

>⚠️ This project is not ment to be used in production. It is a proof of concept and a learning experience for me.
> It will only work on NTFS file systems and using any cloud storage will result in data loss.
> Use at your own risk.

## How it works
WinVCS uses NTFS's Alternate Data Streams to store the contents of files. It also uses a SQLite database to store the metadata of the files.

For more information on how it works, see [thiojoe's video](https://www.youtube.com/watch?v=3BWTo87oCw).

## Some background
I was watching [thiojoe's video](https://www.youtube.com/watch?v=3BWTo87oCw)
[![video_thumbnail](https://img.youtube.com/vi/3BWTo87oCwc/maxresdefault.jpg)](https://www.youtube.com/watch?v=3BWTo87oCwc&t=703s)
when I started reading the comments.
Almost all of them were about how they would hide their "homework" from their parents...

One comment caught my eye. It was about how you could use this to make a version control system.
The comment is by [bwcbiz](https://www.youtube.com/channel/UC3reNJYPnhx5U2PcFz-v_VQ)

![Comment](https://i.imgur.com/exq5dal.png)

bwcbiz, if you're reading this, thank you for the idea! You started an itch that I had to scratch.
this is just a proof of concept and a learning experience for me, so don't expect it to be perfect.

Also, please don't use this in production. it will only work on NTFS file systems and using any cloud storage will result in data loss.
