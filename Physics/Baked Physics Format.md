## Baked Physics Format
---
Even without the use of the Physics flight profile calculator, data of this type will still need to be stored in some way

---
#### .bpf

The simplest way of achiving this would be to create an xml file using a C++ library, then edit the file extension to be .bpf

This would allow me to determine which files are correct when allowing a user to select one of these files

For use with the physics baker, it would be preferable to make use of a zip type format by including both the .obj and related information, and the .bpf file in a zip, keeping all the data for a single aircraft in one place

This method would make it easy to transport and communicate aircraft files