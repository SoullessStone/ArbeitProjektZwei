function sliderSin
% Hudritsch
%Radial = [-0.078112921479421,0.009301585302925,-5.769334157223260e-04];
%Tangential = [-0.0028,0.0058];
% Marcos
%Radial = [-0.1542,0.0685,-0.0173];
%Tangential = [0.0087,0.0009];
% Michel
Radial = [-0.1260,0.0293,-0.0037];
Tangential = [-0.0017,0.0009];
f=figure('visible','off','position',...
    [360 500 900 700]);
k5=uicontrol('style','slider','position',[100 0 200 20],...
    'min',-1,'max',1,'value',Tangential(1),'callback',@callbackfn,'SliderStep',[0.001 0.01]);
k4=uicontrol('style','slider','position',[100 20 200 20],...
    'min',-1,'max',1,'value',Tangential(1),'callback',@callbackfn,'SliderStep',[0.001 0.01]);
k3=uicontrol('style','slider','position',[100 40 200 20],...
    'min',-1,'max',1,'value',Radial(3),'callback',@callbackfn,'SliderStep',[0.001 0.01]);
k2=uicontrol('style','slider','position',[100 60 200 20],...
    'min',-1,'max',1,'value',Radial(2),'callback',@callbackfn,'SliderStep',[0.001 0.01]);
k1=uicontrol('style','slider','position',[100 80 200 20],...
    'min',-1,'max',1,'value',Radial(1),'callback',@callbackfn,'SliderStep',[0.001 0.01]);
valueK1=uicontrol('style','text',...
    'position',[0 80 100 20],'visible','on');
valueK2=uicontrol('style','text',...
    'position',[0 60 100 20],'visible','on');
valueK3=uicontrol('style','text',...
    'position',[0 40 100 20],'visible','on');
valueK4=uicontrol('style','text',...
    'position',[0 20 100 20],'visible','on');
valueK5=uicontrol('style','text',...
    'position',[0 0 100 20],'visible','on');
movegui(f,'center')
callbackfn()
set(f,'visible','on');
    function callbackfn(source,eventdata)
        numK1=get(k1,'value');
        set(valueK1,'visible','on','string',"k1: " + num2str(numK1))
        numK2=get(k2,'value');
        set(valueK2,'visible','on','string',num2str(numK2))
        numK3=get(k3,'value');
        set(valueK3,'visible','on','string',num2str(numK3))
        numK4=get(k4,'value');
        set(valueK4,'visible','on','string',num2str(numK4))
        numK5=get(k5,'value');
        set(valueK5,'visible','on','string',num2str(numK5))
        %Hudritsch
        %IntrinsicMatrix = [5.340156556843946e+02,0,0;-14.486829513920316,4.797480165756543e+02,0;8.420170808008746e+02,5.496006408051229e+02,1];
        % Marcos
        %IntrinsicMatrix = [8.106199311991224e+02,0,0;1.269145680727019,7.356969447856824e+02,0;9.779180765845313e+02,4.986662512331101e+02,1];
        % Michel
        IntrinsicMatrix = [7.965049156873711e+02,0,0;-2.004224765629453,7.312438421776384e+02,0;9.443559918873207e+02,5.082240721288053e+02,1];
        radialDistortion = [numK1,numK2,numK3];
        tangentialDistortion = [numK4,numK5]; 
        cameraParams = cameraParameters('IntrinsicMatrix',IntrinsicMatrix,'RadialDistortion',radialDistortion,'TangentialDistortion',tangentialDistortion); 
        %example = imread('kalibHudritsch.png');
        %example = imread('kalibMarcos.png');
        example = imread('kalibMichel.png');
        undistortedImage = undistortImage(example, cameraParams);
        imshow(undistortedImage);
    end
end